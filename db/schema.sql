CREATE TABLE IF NOT EXISTS readings (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    n INTEGER,
    t_s REAL,
    sensor TEXT,
    value REAL
);

CREATE TABLE IF NOT EXISTS events (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    n INTEGER,
    t_s REAL,
    type TEXT,
    message TEXT
);