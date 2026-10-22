# Создание базы данных SQLite

## Через Python
Находясь в корневой папке проекта, выполните:

```bash
python -c "import sqlite3; c=sqlite3.connect('db/variant.db'); c.executescript(open('db/schema.sql', encoding='utf-8').read()); c.commit(); c.close(); print('База создана: db/variant.db')"
```

## Через SQLite CLI
Если установлен `sqlite3`:

```bash
sqlite3 db/variant.db < db/schema.sql
```

Таблица `readings` хранит показания датчиков (`s1` — температура, `s2` — расстояние, `s3` — крышка).
Таблица `events` хранит события `THRESHOLD`, `NORMAL` и `FAULT`.

Не добавляйте в GitHub реальные пароли, токены или другие секреты.
