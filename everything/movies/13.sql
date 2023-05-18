SELECT DISTINCT name FROM people JOIN stars ON stars.person_id = people.id
WHERE name != 'Kevin Bacon'
AND stars.movie_id IN (SELECT stars.movie_id FROM people JOIN stars ON stars.person_id = people.id
WHERE name = 'Kevin Bacon' AND birth = 1958);