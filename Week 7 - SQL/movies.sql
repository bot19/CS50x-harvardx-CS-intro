-- SQL statements 1-11
SELECT title FROM movies WHERE year = 2008;

SELECT birth FROM people WHERE name = 'Emma Stone';

SELECT title FROM movies WHERE year >= 2018 ORDER BY title;
-- think of arrow funcs "= >" and reverse it = "> =" = greater or equal to

SELECT COUNT(*) FROM movies
WHERE id IN (
    SELECT movie_id FROM ratings
    WHERE rating = 10.0
);

SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year;

SELECT AVG(rating) FROM ratings
WHERE movie_id IN (
    SELECT id FROM movies
    WHERE year = 2012
);

SELECT title, rating FROM movies
    JOIN ratings ON movies.id = ratings.movie_id
    WHERE year = 2010 AND rating IS NOT NULL
    ORDER BY rating DESC, title;

SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM stars
    WHERE movie_id = (
        SELECT id FROM movies
        WHERE title = 'Toy Story'
    )
);
-- CANNOT be SELECT * FROM stars

SELECT DISTINCT name FROM people
WHERE id IN (
    SELECT person_id FROM stars
    WHERE movie_id IN (
        SELECT id FROM movies
        WHERE year = 2004
    )
)
ORDER BY birth;
-- SELECT DISTINCT name FROM people (to remove duplications)
-- they asked for unique names but their results # includes duplicates

SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM directors
    WHERE movie_id IN (
        SELECT movie_id FROM ratings
        WHERE rating >= 9.0
    )
);
-- SELECT DISTINCT... same issue as above
-- this one, left without DISTINCT to match reported numbers (diff vs above)

SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE id IN (
    SELECT movie_id FROM stars
    WHERE person_id = (
        SELECT id FROM people
        WHERE name = 'Chadwick Boseman'
    )
)
ORDER BY rating DESC
LIMIT 5;

-- SQL statement 12

-- a list of movies starring either B or J
SELECT title FROM movies
WHERE id IN (
    SELECT movie_id FROM stars
    WHERE person_id IN (
        SELECT id FROM people
        WHERE name = 'Bradley Cooper' OR name = 'Jennifer Lawrence'
    )
);

-- a list of movies starring BOTH B & J
SELECT title FROM movies
WHERE id IN (
    SELECT movie_id FROM stars
    WHERE person_id = (
        SELECT id FROM people
        WHERE name = 'Bradley Cooper'
    )
)
AND id IN (
    SELECT movie_id FROM stars
    WHERE person_id = (
        SELECT id FROM people
        WHERE name = 'Jennifer Lawrence'
    )
);

-- SQL statement 13

SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM stars
    WHERE movie_id IN (
        SELECT movie_id FROM stars
        WHERE person_id = (
            SELECT id FROM people
            WHERE name = 'Kevin Bacon' AND birth = 1958
        )
    )
)
AND id != (
    SELECT id FROM people
    WHERE name = 'Kevin Bacon' AND birth = 1958
)
ORDER BY name;

-- 1 get the right Kevin Bacon (1958)
-- 2 get all the movies/id he has been in
-- 3 get all the stars/id in these movies
-- 4 get all the names of stars (people)
-- 5 exclude Kevin Bacon himself from results