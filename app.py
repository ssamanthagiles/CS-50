import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # finding all the stocks the user owns and the number of shares for each
    # rows = db.execute("SELECT stock, SUM(shares) as shares FROM transactions WHERE user_id = :user_id GROUP BY stock", user_id=session["user_id"])
    cash_balance = db.execute(
        "SELECT cash FROM users WHERE id = :id", id=session["user_id"]
    )
    print(cash_balance)
    cash_balance = cash_balance[0]["cash"]
    # call the lookup function to get current price:
    # #list of dictionaries: each item of the list represents one share i have
    total_value = cash_balance
    rows = db.execute(
        "SELECT symbol, SUM(shares) FROM transactions WHERE user_id = :user_id GROUP BY symbol",
        user_id=session["user_id"],
    )
    for row in rows:
        stock_info = lookup(row["stock"])
        if stock_info is None:
            #     # handle error, e.g., display message to user
            return apology("Stock symbol was not found")
        row["price"] = stock_info["price"]
        price = stock_info["price"]

        # #total value of each holding (i.e shares times price)
        row["total"] = row["shares"] * price
        total_value = row["total"] + total_value

    # #user's current cash balance along with a grand total
    rows2 = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
    )
    cash_balance = rows2[0]["cash"]
    return render_template(
        "index.html", cash_balance=cash_balance, total_value=total_value
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Getting stock symbol and number of shares
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("Invalid symbol")
    shares = request.form.get("shares")
    if not shares:
        return apology("Missing shares")
    shares = int(shares)
    if lookup(symbol) is None:
        return apology("Invalid stock symbol")
    elif shares <= 0:
        return apology("Invalid number of shares")
    # Checking if stock symbol is valid
    stock_info = lookup(symbol)
    if stock_info is None:
        return apology("Invalid stock symbol")
    # Calculate the total cost of the shares:
    total_cost = stock_info["price"] * shares
    # Check if user has enough balance to buy shares
    balance = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
    )
    if balance[0]["cash"] < total_cost:
        return apology("Doesn't have enough money to buy the shares")
    elif balance[0]["cash"] >= total_cost:
        # Update User's balance
        new_balance = total_cost - balance[0]["cash"]
        db.execute(
            "UPDATE users SET cash = :new_balance WHERE id = :user_id",
            new_balance=new_balance,
            user_id=session["user_id"],
        )
        # Record the transaction:
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            session["user_id"],
            symbol,
            shares,
            stock_info["price"],
        )
    # Return user back to homepage:
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username and is valid
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        # question mark is acting as a place holder for whatever the user is typing into the form

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
    if quote is None:
        return apology("No information about the stock")
    return render_template("quoted.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    # handle GET
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Checking if usernmae and password are empty
        if not username:
            return apology("Username is empty")
        elif not password:
            return apology("Password is empty")
        elif not confirmation:
            return apology("Confirmation password is empty")
        # Checking if the password and confirm password fields equal each other:
        elif password != confirmation:
            # The passwords do not match. Handle this case.
            return apology("Password and confirmation password do not match")

        # Checking the uniqueness of username:
        rows = db.execute(
            "SELECT * FROM users WHERE username = :username", username=username
        )
        if len(rows) != 0:
            return apology("Username already exists")

        # insert new user into database
        hashedpassword = generate_password_hash(password)
        db.execute(
            "INSERT INTO users (username, hash) VALUES (:username, :hash)",
            username=username,
            hash=hashedpassword,
        )

        # gather user id of new registered user
        result = db.execute(
            "SELECT id FROM users WHERE username = :username", username=username
        )
        user_id = result[0]["id"]

        # store user id in session
        session["user_id"] = user_id

        # redirect user back to the homepage
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
