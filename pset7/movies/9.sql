-- write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year

SELECT name FROM people
JOIN stars on stars.person_id = people.id
JOIN movies on stars.movie_id = movies.id
JOIN ratings on ratings.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth;