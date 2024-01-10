-- The names of the top 5 longest songs, in descending order of length.
SELECT
  name
FROM
  songs
ORDER BY
  duration_ms DESC
LIMIT
  5;

-- This selects and returns all the data from the "name" column in the "songs" table
-- and orders results by the duration_ms column in descending order (from highest to lowest)
-- lastly limits the output to top 5 records (essentially gives name of the 5 longest songs in the songs table)