-- write a SQL query to list the names of all people who starred in Toy Story

SELECT name FROM people
JOIN stars on stars.person_id = people.id
JOIN movies on stars.movie_id = movies.id
WHERE movies.title = 'Toy Story';