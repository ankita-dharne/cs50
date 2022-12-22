-- write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0

SELECT name FROM people
JOIN directors on directors.person_id = people.id
JOIN movies on directors.movie_id = movies.id
JOIN ratings on ratings.movie_id = movies.id
WHERE ratings.rating >= 9;