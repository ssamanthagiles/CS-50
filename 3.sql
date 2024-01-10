-- List the titles of all the movies with a release date on or after 2018, in alphabetical order
SELECT
  title
FROM
  movies
WHERE
  YEAR >= 2018
ORDER BY
  title;