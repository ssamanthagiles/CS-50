-- The names of songs that feature other artists.
SELECT
  name
FROM
  songs
WHERE
  name LIKE '%feat.%';

-- using feat. to find out if a song features other artists becasue if it does it says feat. in the song name