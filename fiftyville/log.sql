-- Keep a log of any SQL queries you execute as you solve the mystery.

-- to view all tables
.tables

-- first lets look at crime scene description from crime scene reports on the day and street
SELECT description
FROM crime_scene_reports
WHERE street = "Humphrey Street"
AND year = 2021
AND day = 28
AND month = 7;

--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
--Littering took place at 16:36. No known witnesses.


-- next im going to look at transcript and people in interviews for that day
SELECT transcript, name
FROM interviews
WHERE year = 2021
AND day = 28
AND month = 7;

-- | Barbara |
 --Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
 --  Ruth    |
--| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money
--| Eugene  |
--| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket


--Things to do
-- look at bakery car park 10:15-10:25 for cars leaving 28th july 2021
SELECT activity, license_plate
FROM bakery_security_logs
WHERE year = 2021
AND day = 28
AND month = 7
AND hour = 10
AND minute BETWEEN 15 AND 25;
+----------+---------------+
| activity | license_plate |
+----------+---------------+
| exit     | 5P2BI95       |
| exit     | 94KL13X       |
| exit     | 6P58WS2       |
| exit     | 4328GD8       |
| exit     | G412CB7       |
| exit     | L93JTIZ       |
| exit     | 322W7JE       |
| exit     | 0NTHK55       |
+----------+---------------+

-- look at people who have a car with these number plates
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE license_plate IN ("5P2BI95", "94KL13X","6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55");

+---------+----------------+-----------------+---------------+
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+---------+----------------+-----------------+---------------+


--look at calls less than a minute between 10:15 - 10:25 with the numbers from above

SELECT caller, receiver, duration
FROM phone_calls
WHERE year = 2021
AND day = 28
AND month = 7
AND duration BETWEEN 0 AND 60;

+----------------+----------------+----------+
|     caller     |    receiver    | duration |
+----------------+----------------+----------+
| (130) 555-0289 | (996) 555-8899 | 51       |
| (499) 555-9472 | (892) 555-8872 | 36       |
| (367) 555-5533 | (375) 555-8161 | 45       |
| (609) 555-5876 | (389) 555-5198 | 60       |
| (499) 555-9472 | (717) 555-1342 | 50       |
| (286) 555-6063 | (676) 555-6554 | 43       |
| (770) 555-1861 | (725) 555-3243 | 49       |
| (031) 555-6622 | (910) 555-3251 | 38       |
| (826) 555-1652 | (066) 555-9701 | 55       |
| (338) 555-6650 | (704) 555-2131 | 54       |
+----------------+----------------+----------+

-- next look at the callers from that list and see if they match any of those licence plate owners

SELECT DISTINCT name, passport_number
FROM people
JOIN phone_calls
ON phone_calls.caller = people.phone_number
WHERE phone_calls.caller IN
    (SELECT caller
    FROM phone_calls
    WHERE year = 2021
    AND day = 28
    AND month = 7
    AND duration BETWEEN 0 AND 60)
;

+---------+-----------------+
|  name   | passport_number |
+---------+-----------------+
| Bruce   | 5773159633      |
| Taylor  | 1988161715      |
| Kelsey  | 8294398571      |
| Sofia   | 1695452385      |
| Diana   | 3592750733      |
| Carina  | 9628244268      |
| Benista | 9586786673      |
| Kenny   | 9878712108      |
| Kathryn | 6121106406      |
+---------+-----------------+


-- look up the people who recieved the call in the same time frame:
SELECT DISTINCT name, passport_number
FROM people
JOIN phone_calls
ON phone_calls.caller = people.phone_number
WHERE phone_calls.receiver IN
    (SELECT receiver
    FROM phone_calls
    WHERE year = 2021
    AND day = 28
    AND month = 7
    AND duration BETWEEN 0 AND 60)
;

+-----------+-----------------+
|   name    | passport_number |
+-----------+-----------------+
| Arthur    | 7884829354      |
| Jesse     |                 |
| Sophia    | 3642612721      |
| Sofia     | 1695452385      |
| Kelsey    | 8294398571      |
| Walter    | 4223654265      |
| Bruce     | 5773159633      |
| Kathryn   | 6121106406      |
| Christine |                 |
| Virginia  | 3866596772      |
| Taylor    | 1988161715      |
| Diana     | 3592750733      |
| Carina    | 9628244268      |
| Logan     | 9692634019      |
| Kenny     | 9878712108      |
| Benista   | 9586786673      |
| Rebecca   | 6264773605      |
| Sean      | 4377966420      |
| Samantha  | 6720918005      |
| Steven    | 1151340634      |
| Jose      | 9183348466      |
| Jonathan  | 2047409662      |
| Margaret  | 1782675901      |
| Ronald    | 4959515588      |
| Grace     | 9826028703      |
| Catherine |                 |
| Thomas    | 6034823042      |
| Lisa      |                 |
| Ashley    | 1038053449      |
+-----------+-----------------+


-- look at first flight out of fiftyville 29th july 2021

SELECT id, origin_airport_id, destination_airport_id
FROM flights
WHERE year = 2021
AND day = 29
AND month = 7
ORDER BY hour ASC, minute ASC
LIMIT 1;
+----+-------------------+------------------------+
| id | origin_airport_id | destination_airport_id |
+----+-------------------+------------------------+
| 36 | 8                 | 4                      |
+----+-------------------+------------------------+

-- look up airport destination by code 4

SELECT full_name, city
FROM airports
WHERE id = 4;
+-------------------+---------------+
|     full_name     |     city      |
+-------------------+---------------+
| LaGuardia Airport | New York City |
+-------------------+---------------+

-- so they went to new york.


-- look atm withdrawals on leggatt street 28th july 2021 morning
SELECT account_number, transaction_type
FROM atm_transactions
WHERE atm_location = "Leggett Street"
AND year = 2021
AND day = 28
AND month = 7
AND transaction_type = "withdraw";
+----------------+------------------+
| account_number | transaction_type |
+----------------+------------------+
| 28500762       | withdraw         |
| 28296815       | withdraw         |
| 76054385       | withdraw         |
| 49610011       | withdraw         |
| 16153065       | withdraw         |
| 25506511       | withdraw         |
| 81061156       | withdraw         |
| 26013199       | withdraw         |
+----------------+------------------+

-- match the account numbers to the people - by joining atm, band account and people tables

SELECT DISTINCT name
FROM people
JOIN bank_accounts
ON bank_accounts.person_id = people.id
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number
WHERE bank_accounts.account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE atm_location = "Leggett Street"
    AND year = 2021
    AND day = 28
    AND month = 7
    AND transaction_type = "withdraw"
);
|  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |


-- now see which of those who made a withdrawal people were on the flight

SELECT name, seat
FROM passengers
JOIN people
ON people.passport_number = passengers.passport_number
WHERE passengers.passport_number IN (
    SELECT passport_number
    FROM people
    JOIN bank_accounts
    ON bank_accounts.person_id = people.id
    JOIN atm_transactions
    ON atm_transactions.account_number = bank_accounts.account_number
    WHERE bank_accounts.account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE atm_location = "Leggett Street"
        AND year = 2021
        AND day = 28
        AND month = 7
        AND transaction_type = "withdraw"
        )
)
AND flight_id = 36;


|  name  | seat |
+--------+------+
| Bruce  | 4A   |
| Taylor | 6D   |
| Kenny  | 7A   |
| Luca   | 7B   |

-- now look and see if any one from that list, matches someone from the table who made calls:

SELECT DISTINCT name
FROM people
JOIN phone_calls
ON phone_calls.caller = people.phone_number
WHERE phone_calls.caller IN
    (SELECT caller
    FROM phone_calls
    WHERE year = 2021
    AND day = 28
    AND month = 7
    AND duration BETWEEN 0 AND 60)
AND name IN (
    SELECT name
    FROM passengers
    JOIN people
    ON people.passport_number = passengers.passport_number
    WHERE passengers.passport_number IN (
        SELECT passport_number
        FROM people
        JOIN bank_accounts
        ON bank_accounts.person_id = people.id
        JOIN atm_transactions
        ON atm_transactions.account_number = bank_accounts.account_number
        WHERE bank_accounts.account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE atm_location = "Leggett Street"
            AND year = 2021
            AND day = 28
            AND month = 7
            AND transaction_type = "withdraw"
            )
    )
    AND flight_id = 36
);

| Kenny  |
| Taylor |
| Bruce  |


-- now look and see if any one from the list, matches someone from the table who recieved calls:

SELECT DISTINCT name
FROM people
JOIN phone_calls
ON phone_calls.caller = people.phone_number
WHERE phone_calls.receiver IN
    (SELECT receiver
    FROM phone_calls
    WHERE year = 2021
    AND day = 28
    AND month = 7
    AND duration BETWEEN 0 AND 60)
AND name IN (
    SELECT name
    FROM passengers
    JOIN people
    ON people.passport_number = passengers.passport_number
    WHERE flight_id = 36
);

+--------+
|  name  |
+--------+
| Kenny  |
| Sofia  |
| Taylor |
| Kelsey |
| Bruce  |


-- so we have these as potential  thief:
| Kenny  |
| Taylor |
| Bruce  |
-- lets see if any match any of the licences in the car park:

SELECT DISTINCT name
FROM people
JOIN phone_calls
ON phone_calls.caller = people.phone_number
WHERE phone_calls.caller IN
    (SELECT caller
    FROM phone_calls
    WHERE year = 2021
    AND day = 28
    AND month = 7
    AND duration BETWEEN 0 AND 60)
AND name IN (
    SELECT name
    FROM passengers
    JOIN people
    ON people.passport_number = passengers.passport_number
    WHERE passengers.passport_number IN (
        SELECT passport_number
        FROM people
        JOIN bank_accounts
        ON bank_accounts.person_id = people.id
        JOIN atm_transactions
        ON atm_transactions.account_number = bank_accounts.account_number
        WHERE bank_accounts.account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE atm_location = "Leggett Street"
            AND year = 2021
            AND day = 28
            AND month = 7
            AND transaction_type = "withdraw"
            )
    )
    AND flight_id = 36
    AND name in (
        SELECT name
        FROM people
        WHERE license_plate IN ("5P2BI95", "94KL13X","6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55")
    )
);

-- we have the theif!
| name  |
+-------+
| Bruce |


-- finally lets see who bruce called which is the accompliace

SELECT name
FROM people
WHERE phone_number = (
    SELECT receiver
    FROM phone_calls
    WHERE caller = (
        SELECT phone_number
        FROM people
        WHERE name = "Bruce"
    )
    AND year = 2021
    AND day = 28
    AND month = 7
    AND duration BETWEEN 0 AND 60
);

Accompliace is
| name  |
+-------+
| Robin |



