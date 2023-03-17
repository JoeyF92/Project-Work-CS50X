 SELECT name
 FROM people
 JOIN stars ON stars.person_id = people.id
 JOIN movies on stars.movie_id = movies.id
 WHERE movies.title = "Toy Story";