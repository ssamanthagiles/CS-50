-- The average energy of songs that are by Drake !! - favorite artist :)
SELECT
  AVG(energy)
FROM
  songs
  JOIN artists ON songs.artist_id = artists.id
WHERE
  artists.name = 'Drake';