-- 1. Десять последних показаний
SELECT n, t_s, sensor, value
FROM readings
ORDER BY n DESC, sensor
LIMIT 10;

-- 2. Минимум, среднее и максимум для каждого датчика
SELECT sensor, MIN(value) AS min_value,
       ROUND(AVG(value), 3) AS avg_value,
       MAX(value) AS max_value
FROM readings
GROUP BY sensor;

-- 3. Все события по времени
SELECT n, t_s, type, message
FROM events
ORDER BY n, id;
