--write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
SELECT
  name
FROM
  people
WHERE
  id IN (
    SELECT
      person_id
    FROM
      stars
    WHERE
      movie_id IN (
        SELECT
          movie_id
        FROM
          stars
        WHERE
          person_id IN (
            SELECT
              id
            FROM
              people
            WHERE
              name = 'Kevin Bacon'
              AND birth = 1958
          )
      )
  )
  AND id != (
    SELECT
      id
    FROM
      people
    WHERE
      name = 'Kevin Bacon'
      AND birth = 1958
  )
ORDER BY
  name;

-- started problem sets songs at office hours at 7pm at HSA Floor 4 on 6/4
--finisehd both problem sets on my own with the help of the cs50.ai duck !!