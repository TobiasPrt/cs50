SELECT DISTINCT(title) FROM people 
    JOIN stars ON people.id = stars.person_id 
    JOIN movies ON stars.movie_id = movies.id 
        WHERE people.name = "Johnny Depp" 
        AND
        movies.id 
            IN (SELECT movies.id FROM people 
                JOIN stars ON people.id = stars.person_id 
                JOIN movies ON stars.movie_id = movies.id 
                    WHERE people.name = "Helena Bonham Carter");