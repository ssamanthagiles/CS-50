import cs50


## this step is prompting the user to see how much chagne is owed, in cents by multiplying it by 100 and then rounding
change_owed = None
while change_owed is None or change_owed <= 0:
    change_owed = float(cs50.get_float("Change owed: ")) * 100
change_owed = round(change_owed)

##initializing a variable coins to keep track of the total number of coins being used
coins = 0
## Calculating the number of quarters
quarters = change_owed // 25
# Amount of change left after giving out as many quarters as possible:
change_owed = change_owed % 25
## updating change owed & coins
coins = coins + quarters

## Calculating the number of dimes
dimes = change_owed // 10
# Amount of change left after giving out as many dimes as possible:
change_owed = change_owed % 10
## updating change owed & coins
coins = coins + dimes

## Calculating the number of nickels
nickels = change_owed // 5
# Amount of change left after giving out as many quarters as possible:
change_owed = change_owed % 5
## updating change owed & coins
coins = coins + nickels

## Calculating the number of pennies
pennies = change_owed // 1
# Amount of change left after giving out as many quarters as possible:
change_owed = change_owed % 1
## updating change owed & coins
coins = coins + pennies

##printing the number of coins after everything has been updated
print(coins)


## started on 10/28 and finished in office hours at widener library on 10/29 with the help of CA, João Henrique Santos
