SELECT
  name
FROM
  songs
WHERE
  artist_id = (
    SELECT
      id
    FROM
      artists
    WHERE
      name = 'Post Malone'
  );

--This command will first execute the subquery (SELECT id FROM artists WHERE name = 'Post Malone') to find the id of 'Post Malone' in the "artists" table. Then, it will select all the song names from the "songs" table where the artist_id matches the id of 'Post Malone'.