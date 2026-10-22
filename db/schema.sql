PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS readings (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    n INTEGER NOT NULL,
    t_s INTEGER NOT NULL,
    sensor TEXT NOT NULL CHECK(sensor IN ('s1','s2','s3')),
    value REAL NOT NULL,
    UNIQUE(n, sensor)
);

CREATE TABLE IF NOT EXISTS events (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    n INTEGER NOT NULL,
    t_s INTEGER NOT NULL,
    type TEXT NOT NULL CHECK(type IN ('THRESHOLD','NORMAL','FAULT')),
    message TEXT
);

CREATE INDEX IF NOT EXISTS idx_readings_sensor_n ON readings(sensor, n);
CREATE INDEX IF NOT EXISTS idx_events_n ON events(n);
