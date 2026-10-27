SELECT * FROM readings ORDER BY id DESC LIMIT 10;
SELECT 
    sensor, 
    MIN(value) AS min_v, 
    ROUND(AVG(value), 2) AS avg_v, 
    MAX(value) AS max_v 
FROM readings 
GROUP BY sensor;

SELECT * FROM events ORDER BY id;