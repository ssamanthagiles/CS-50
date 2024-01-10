-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Starting with the crime scene by pulling up data where the crime scene report is:
SELECT
  description
FROM
  crime_scene_reports
WHERE
  YEAR = 2023
  AND MONTH = 7
  AND DAY = 28;

-- What is found from above query:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at the time – each of their interview
--transcripts mentions the bakery. |
--Finding what witness' said:
SELECT
  *
FROM
  interviews
WHERE
  transcript LIKE '%bakery%'
  AND YEAR = 2023
  AND MONTH = 7
  AND DAY = 28;

-- Some of what is found:
--Ruth: "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame
--Following, Ruth's instructions and now looking for cars in the parking lot during that time frame:
-- But first need to find what activity does in the bakery_security_logs table:
SELECT
  activity
FROM
  bakery_security_logs;

-- Found that it returns exit !! going to check exit here:
SELECT
  name
FROM
  people
WHERE
  license_plate IN (
    SELECT
      license_plate
    FROM
      bakery_security_logs
    WHERE
      YEAR = 2023
      AND MONTH = 7
      AND DAY = 28
      AND HOUR = 10
      AND MINUTE > 15
      AND MINUTE < 25
      AND activity = 'exit'
  );

-- Now we have 8 names: Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce
-- Remember other hint: "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money."
SELECT
  id
FROM
  atm_transactions
WHERE
  YEAR = 2023
  AND MONTH = 7
  AND DAY = 28
  AND atm_location = 'Leggett Street';

--id's that i got: -----+ 246, 264, 266, 267, 269, 275, 288, 313, 336
--testing what i can find for transaction type:
SELECT
  transaction_type
FROM
  atm_transactions;

--now doing:
SELECT
  bakery_security_logs.license_plate,
  people.name
FROM
  bakery_security_logs
  JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE
  YEAR = 2023
  AND MONTH = 7
  AND DAY = 28
  AND MINUTE > 15
  AND MINUTE < 25
  AND activity = 'exit';

--Found the license plates of each of the suspects from the query above ^
SELECT
  account_number
FROM
  atm_transactions
WHERE
  transaction_type = "withdraw"
  AND atm_location = "Leggett Street"
  AND DAY = 28
  AND YEAR = 2023
  AND MONTH = 7;

--YAY found the account numbers, almost there !
-- With all the information I've found, now it's time to link the info of bank account numbers, people, and atm transactions to find the robbers !!
SELECT
  name
FROM
  people
  JOIN bank_accounts ON people.id = bank_accounts.person_id
  JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE
  YEAR = 2023
  AND DAY = 28
  AND MONTH = 7
  AND atm_location = "Leggett Street"
  AND transaction_type = "withdraw";

-- Now with the query above I have a list of suspsects: Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista
--Have to look at list of suspects before and see the ones that are both listed!
--(liST  of suspects before): Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce
-- So narrowed down to Bruce, Diana, Iman, Luca
-- In order to further narrow have to reference previous hint: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- using this hint to look at the flights, airports, people, and passengers to see who flew out the day after 7/28/2023
SELECT
  people.name,
  HOUR
FROM
  people
  JOIN passengers ON passengers.passport_number = people.passport_number
  --finding the passport number
  JOIN flights ON passengers.flight_id = flights.id
  --finding the passenger on the flight's id
  JOIN airports ON flights.origin_airport_id = airports.id
  --finding which airport !! this is important
WHERE
  city = "Fiftyville"
  AND YEAR = 2023
  AND DAY = 29
  AND MONTH = 7
  --making sure they fly out of Fiftyville (and it's the day after which we know from the hint)
ORDER BY
  HOUR
  --searching for earliest flight
LIMIT
  7;

--Now remeber the hint, it's the earliest flight (which is 8)
--Passengers on the flight at hour 8:
--Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca
-- Refrencing most simplified list of suspects:
--Bruce, Diana, Iman, Luca
---Omg the criminal is BRUCE
--Finding the airport that bruce went to on his flight in order to track him down:
SELECT
  city
FROM
  airports
WHERE
  id IN (
    SELECT
      flights.destination_airport_id
    FROM
      flights
      JOIN airports ON flights.origin_airport_id = airports.id
    WHERE
      city = 'Fiftyville'
      AND YEAR = 2023
      AND DAY = 29
      AND MONTH = 7
    ORDER BY
      HOUR
    LIMIT
      1
  );

--OMG he escaped to NYC !!
SELECT
  name
FROM
  people
WHERE
  phone_number IN (
    SELECT
      receiver
    FROM
      phone_calls
      JOIN people ON phone_calls.caller = people.phone_number
    WHERE
      YEAR = 2023
      AND DAY = 28
      AND MONTH = 7
      AND duration <= 60
      AND caller IN (
        SELECT
          phone_number
        FROM
          people
        WHERE
          name = "Bruce"
      )
  );

-- THIS is making sure the phone call was from Bruce in order to find the accomplice
--Found that the accomplice is ROBin
-- Went to Office hOurs at widener library today from 3 - 5 to complete the problem set and receieved help from multiple cas