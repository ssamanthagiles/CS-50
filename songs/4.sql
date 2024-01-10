-- The names of any songs that have danceability, energy, and valence greater than 0.75.
SELECT
  name
FROM
  songs
WHERE
  danceability > 0.75
  AND energy > 0.75
  AND valence > 0.75;

-- essentially is a query that selects the name column from songs table where dancebility, energy, and valence values are greater than .75 (which are the names of songs that have a dancebility, energy, and valence score higher than .75) )