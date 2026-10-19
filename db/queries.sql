-- 1. 10 последних показаний
SELECT * FROM readings ORDER BY t_s DESC LIMIT 10;

-- 2. Минимум, среднее и максимум по каждому датчику
SELECT 
    sensor,
    MIN(value) AS min_value,
    ROUND(AVG(value), 2) AS avg_value,
    MAX(value) AS max_value
FROM readings 
GROUP BY sensor;

-- 3. Все события по порядку
SELECT * FROM events ORDER BY t_s ASC;