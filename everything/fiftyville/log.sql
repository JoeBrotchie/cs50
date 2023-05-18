-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Chamberlin STreet';
--duck stolen at 10:15am at the Humphrey Street bakery.
--3 witnesses mentions the bakery
SELECT transcript FROM interviews
WHERE month = 7 AND day = 28;
--Ruth said it was within 10 mins and the theif drove off
--Eugene said he recognized the theif saw them withdrawing some money at the ATM on Leggett Street
--Raymond said the theif called someone (lasted less then a min) and said to the person on the other end to make a purchase of a plane ticket for the next day earlyist possible
SELECT full_name FROM airports WHERE full_name LIKE '%Fiftyville%';
--air port name = Fiftyville Regional Airport and abbreviation = CSF
SELECT full_name, hour FROM airports JOIN flights ON airports.id = flights.origin_airport_id
WHERE month = 7 AND day = 29
ORDER BY hour;
--then i did the same for destination and found the earlyest flight out of Fifyville was at 8 and went to LaGuardia Airport
SELECT city FROM airports WHERE full_name = 'LaGuardia Airport';
--the theif goes to new york city
SELECT caller, receiver FROM phone_calls
WHERE duration < 60 AND month = 7 AND day = 28
AND caller IN (SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND minute > 14 AND minute < 25));
--this gives a list of all possible theifs and accomplisses numbers
SELECT id FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE duration < 60 AND month = 7 AND day = 28
AND caller IN (SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND minute > 14 AND minute < 25)));
--all people id that exited the backery shop that could be the suspect
SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE atm_location = 'Leggett Street' AND month = 7 AND day = 28 AND transaction_type = 'withdraw');
--this gives a list of all people that widthdrew monney in the morning on legget street
SELECT passport_number FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE atm_location = 'Leggett Street' AND month = 7 AND day = 28 AND transaction_type = 'withdraw')
AND person_id IN (SELECT id FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE duration < 60 AND month = 7 AND day = 28
AND caller IN (SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND minute > 14 AND minute < 25)))));
--combo them and you get 2 id's of possible theifs there for you can find there passport number and see if they got on the flight to new york
SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT flights.id FROM flights
WHERE month = 7 AND day = 29 AND hour = 8);
--got all passport numbers from the plane the theif is on
SELECT passport_number FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE atm_location = 'Leggett Street' AND month = 7 AND day = 28 AND transaction_type = 'withdraw')
AND person_id IN (SELECT id FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE duration < 60 AND month = 7 AND day = 28
AND caller IN (SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND minute > 14 AND minute < 25)))))
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT flights.id FROM flights
WHERE month = 7 AND day = 29 AND hour = 8));
--combo them and you get 1 passport id (the theif)
SELECT name FROM people WHERE passport_number IN
(SELECT passport_number FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE atm_location = 'Leggett Street' AND month = 7 AND day = 28 AND transaction_type = 'withdraw')
AND person_id IN (SELECT id FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE duration < 60 AND month = 7 AND day = 28
AND caller IN (SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND minute > 14 AND minute < 25)))))
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT flights.id FROM flights
WHERE month = 7 AND day = 29 AND hour = 8)));
--gives the name of the theif
SELECT caller, receiver FROM phone_calls
WHERE month = 7 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number FROM people WHERE passport_number IN
(SELECT passport_number FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE atm_location = 'Leggett Street' AND month = 7 AND day = 28 AND transaction_type = 'withdraw')
AND person_id IN
(SELECT id FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE duration < 60 AND month = 7 AND day = 28
AND caller IN
(SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND minute > 14 AND minute < 25)))))
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT flights.id FROM flights
WHERE month = 7 AND day = 29 AND hour = 8))));
--gives caller (number for theif) and receiver (number for ACCOMPLICE)
SELECT name FROM people
WHERE phone_number = '(367) 555-5533';
--there for bruce is the theif
SELECT name FROM people
WHERE phone_number = '(375) 555-8161';