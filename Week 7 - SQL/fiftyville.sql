-- Keep a log of any SQL queries you execute as you solve the mystery.

-- start, initial crime details for leads
SELECT * FROM crime_scene_reports
WHERE day = 28
    AND month = 7
    AND year = 2024
    AND street = 'Humphrey Street';

-- 3 witnesses, interviewed same day, transcript mentions 'bakery'
SELECT * FROM interviews
WHERE day = 28
    AND month = 7
    AND year = 2024
    AND transcript LIKE '%bakery%';

-- clue 2: ATM, Leggett st, before 1015am day of crime, withdraw
SELECT * FROM atm_transactions
WHERE day = 28
    AND month = 7
    AND year = 2024
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';

-- clue 1: 1015-1025am, bakery parking, thief drives off
SELECT * FROM bakery_security_logs
WHERE day = 28
    AND month = 7
    AND year = 2024
    AND hour = 10
    AND minute >= 15
    AND minute <= 25;

-- clue 3: 1015-1025am, call someone, <1m, earliest flight out, buy flight ticket
SELECT * FROM phone_calls
WHERE day = 28
    AND month = 7
    AND year = 2024
    AND duration <= 60;

-- figure out people from 10 caller phone numbers of interest > license plate
SELECT * FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE day = 28
    AND month = 7
    AND year = 2024
    AND duration <= 60;

-- same as above, but show people with matching license plates = 4 people
SELECT * FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE day = 28
    AND month = 7
    AND year = 2024
    AND duration <= 60
    AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE day = 28
            AND month = 7
            AND year = 2024
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
    );

-- check which of 4 people accessed ATM at time/place of interest = 2 (514354, 686048)
SELECT * FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE day = 28
    AND month = 7
    AND year = 2024
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
    AND (
        person_id = 398010
        OR person_id = 560886
        OR person_id = 686048
        OR person_id = 514354
    );

-- get airport info; 4 | LGA | LaGuardia Airport | New York City
SELECT * FROM airports;

-- check earliest flight out next day for these 2 people = id 36, dest. 4, 8:20
SELECT * FROM flights
WHERE origin_airport_id = (
    SELECT id FROM airports
    WHERE city = 'Fiftyville'
)
    AND day = 29
    AND month = 7
    AND year = 2024
ORDER BY hour, minute;

-- check for the 2 people of interest on above flight's passenger list = Bruce
SELECT * FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
WHERE flight_id = 36
    AND passengers.passport_number IN (
        SELECT passport_number FROM people
        WHERE id = 514354 OR id = 686048
    );

-- find out Bruce's accomplice via phone_calls.receiver = Robin
SELECT * FROM people
WHERE phone_number = (
    SELECT receiver FROM people
    JOIN phone_calls ON phone_calls.caller = people.phone_number
    WHERE day = 28
        AND month = 7
        AND year = 2024
        AND duration <= 60
        AND name = 'Bruce'
);
