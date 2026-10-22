# Создание репозитория GitHub

## Вариант A — через сайт (проще всего)
1. Войдите в GitHub самостоятельно.
2. Нажмите `+` → `New repository`.
3. Имя: `payment-terminal-variant-7`.
4. Выберите `Public` или `Private` по требованиям преподавателя.
5. Не добавляйте README, .gitignore и лицензию на сайте, если эти файлы уже есть в локальной папке.
6. Нажмите `Create repository`.
7. Скопируйте HTTPS URL созданного репозитория.

## Загрузка проекта из терминала
Откройте терминал в корневой папке проекта и выполните:

```bash
git init
git add README.md CREATE_DATABASE.md GITHUB_SETUP.md src db data docs
git commit -m "Добавлен проект платёжного терминала, вариант 7"
git branch -M main
git remote add origin https://github.com/ВАШ_ЛОГИН/payment-terminal-variant-7.git
git push -u origin main
```

Замените `ВАШ_ЛОГИН` на свой логин GitHub и URL на адрес репозитория, который GitHub показал после создания. Если Git сообщает, что `origin` уже существует, используйте:
`git remote set-url origin https://github.com/ВАШ_ЛОГИН/payment-terminal-variant-7.git`

## Вариант B — GitHub CLI
Если установлен `gh` и вы уже вошли командой `gh auth login`, из папки проекта выполните:

```bash
gh repo create payment-terminal-variant-7 --public --source=. --remote=origin --push
```

Для закрытого репозитория замените `--public` на `--private`.

## Важно
- Не передавайте пароль от GitHub в чат или в команды.
- Для HTTPS Git обычно использует браузерную авторизацию или credential manager; если нужен токен, создайте его самостоятельно на GitHub и никому не показывайте.
- База `db/variant.db` может быть загружена как учебный файл, но при командной работе часто удобнее хранить `db/schema.sql`, а базу генерировать локально.
