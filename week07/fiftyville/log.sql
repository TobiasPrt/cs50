-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Used to get a birds-eye overview over all the tables and data in the database
.schema

-- Get Description of crime
SELECT description FROM crime_scene_reports 
    WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Get Interview transscript from the same day, which mention courthouse
SELECT transcript FROM interviews WHERE transcript LIKE "%courthouse%" AND month = 7 AND day = 28;

-- Start building query with first getting all people withdrawing money that day
SELECT people.name, atm_transactions.year FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
        WHERE atm_transactions.month = 7
            AND atm_transactions.day = 28
            AND atm_transactions.transaction_type = "withdraw";

-- Continue building up that query to include the security logs as well
SELECT people.name FROM people
    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
        WHERE atm_transactions.month = 7
            AND atm_transactions.day = 28
            AND atm_transactions.transaction_type = "withdraw"
            AND atm_transactions.atm_location = "Fifer Street"
            AND courthouse_security_logs.month = 7
            AND courthouse_security_logs.day = 28
            AND courthouse_security_logs.minute >= 15
            AND courthouse_security_logs.minute <= 25
            AND courthouse_security_logs.hour = 10
            AND courthouse_security_logs.activity = "exit";

-- After that only Ernest, Russell, Elizabeth and Danielle are possible thieves
-- Now this query will be built up even more by adding the phone call log as well
SELECT phone_calls.caller FROM people
    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    JOIN phone_calls ON people.phone_number = phone_calls.caller
        WHERE atm_transactions.month = 7
            AND atm_transactions.day = 28
            AND atm_transactions.transaction_type = "withdraw"
            AND atm_transactions.atm_location = "Fifer Street"
            AND courthouse_security_logs.month = 7
            AND courthouse_security_logs.day = 28
            AND courthouse_security_logs.minute >= 15
            AND courthouse_security_logs.minute <= 25
            AND courthouse_security_logs.hour = 10
            AND courthouse_security_logs.activity = "exit"
            AND phone_calls.day = 28
            AND phone_calls.month = 7
            AND phone_calls.duration <= 60;

-- Now only Russell and Ernest are left
-- Now see if any of them flies tomorrow
SELECT people.name FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
        WHERE flights.month = 7
        AND flights.day = 29
        AND people.name
            IN (SELECT people.name FROM people
                    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
                    JOIN bank_accounts ON people.id = bank_accounts.person_id
                    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                    JOIN phone_calls ON people.phone_number = phone_calls.caller
                        WHERE atm_transactions.month = 7
                            AND atm_transactions.day = 28
                            AND atm_transactions.transaction_type = "withdraw"
                            AND atm_transactions.atm_location = "Fifer Street"
                            AND courthouse_security_logs.month = 7
                            AND courthouse_security_logs.day = 28
                            AND courthouse_security_logs.minute >= 15
                            AND courthouse_security_logs.minute <= 25
                            AND courthouse_security_logs.hour = 10
                            AND courthouse_security_logs.activity = "exit"
                            AND phone_calls.day = 28
                            AND phone_calls.month = 7
                            AND phone_calls.duration <= 60);

-- both fly tomorrow, so look if one is on an earlier flight
SELECT people.name FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.destination_airport_id = airports.id
        WHERE flights.month = 7
        AND flights.day = 29
        AND people.name
            IN (SELECT people.name FROM people
                    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
                    JOIN bank_accounts ON people.id = bank_accounts.person_id
                    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                    JOIN phone_calls ON people.phone_number = phone_calls.caller
                        WHERE atm_transactions.month = 7
                            AND atm_transactions.day = 28
                            AND atm_transactions.transaction_type = "withdraw"
                            AND atm_transactions.atm_location = "Fifer Street"
                            AND courthouse_security_logs.month = 7
                            AND courthouse_security_logs.day = 28
                            AND courthouse_security_logs.minute >= 15
                            AND courthouse_security_logs.minute <= 25
                            AND courthouse_security_logs.hour = 10
                            AND courthouse_security_logs.activity = "exit"
                            AND phone_calls.day = 28
                            AND phone_calls.month = 7
                            AND phone_calls.duration <= 60)
        ORDER BY flights.hour ASC, flights.minute ASC
        LIMIT 1;

-- Ernest is the thief
-- Now find the destination city
SELECT people.name FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
        WHERE flights.month = 7
        AND flights.day = 29
        AND people.name
            IN (SELECT people.name FROM people
                    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
                    JOIN bank_accounts ON people.id = bank_accounts.person_id
                    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                    JOIN phone_calls ON people.phone_number = phone_calls.caller
                        WHERE atm_transactions.month = 7
                            AND atm_transactions.day = 28
                            AND atm_transactions.transaction_type = "withdraw"
                            AND atm_transactions.atm_location = "Fifer Street"
                            AND courthouse_security_logs.month = 7
                            AND courthouse_security_logs.day = 28
                            AND courthouse_security_logs.minute >= 15
                            AND courthouse_security_logs.minute <= 25
                            AND courthouse_security_logs.hour = 10
                            AND courthouse_security_logs.activity = "exit"
                            AND phone_calls.day = 28
                            AND phone_calls.month = 7
                            AND phone_calls.duration <= 60)
        ORDER BY flights.hour ASC, flights.minute ASC
        LIMIT 1;

-- Destination is London

-- First get flight id for a simpler query
SELECT flights.id FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
        WHERE flights.month = 7
        AND flights.day = 29
        AND people.name
            IN (SELECT people.name FROM people
                    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
                    JOIN bank_accounts ON people.id = bank_accounts.person_id
                    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                    JOIN phone_calls ON people.phone_number = phone_calls.caller
                        WHERE atm_transactions.month = 7
                            AND atm_transactions.day = 28
                            AND atm_transactions.transaction_type = "withdraw"
                            AND atm_transactions.atm_location = "Fifer Street"
                            AND courthouse_security_logs.month = 7
                            AND courthouse_security_logs.day = 28
                            AND courthouse_security_logs.minute >= 15
                            AND courthouse_security_logs.minute <= 25
                            AND courthouse_security_logs.hour = 10
                            AND courthouse_security_logs.activity = "exit"
                            AND phone_calls.day = 28
                            AND phone_calls.month = 7
                            AND phone_calls.duration <= 60)
        ORDER BY flights.hour ASC, flights.minute ASC
        LIMIT 1;

-- Find number ernest has called
SELECT phone_calls.receiver FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.destination_airport_id = airports.id
        WHERE flights.month = 7
        AND flights.day = 29
        AND people.name
            IN (SELECT people.name FROM people
                    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
                    JOIN bank_accounts ON people.id = bank_accounts.person_id
                    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                    JOIN phone_calls ON people.phone_number = phone_calls.caller
                        WHERE atm_transactions.month = 7
                            AND atm_transactions.day = 28
                            AND atm_transactions.transaction_type = "withdraw"
                            AND atm_transactions.atm_location = "Fifer Street"
                            AND courthouse_security_logs.month = 7
                            AND courthouse_security_logs.day = 28
                            AND courthouse_security_logs.minute >= 15
                            AND courthouse_security_logs.minute <= 25
                            AND courthouse_security_logs.hour = 10
                            AND courthouse_security_logs.activity = "exit"
                            AND phone_calls.day = 28
                            AND phone_calls.month = 7
                            AND phone_calls.duration <= 60)
        ORDER BY flights.hour ASC, flights.minute ASC
        LIMIT 1;

-- Flight ID is 36
-- Now find accomplice
SELECT * FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
        WHERE phone_calls.caller = "(367) 555-5533"
        AND phone_calls.day = 28
        AND phone_calls.month = 7
        AND phone_calls.duration <= 60;


-- Its Berthold OMG

