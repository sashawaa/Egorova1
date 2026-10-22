// Node-RED Function node: вход msg.payload — текст всего data/log.txt.
// Выход 1: SQL INSERT для readings; выход 2: SQL INSERT для events.
// Для sqlite-узла настройте параметризацию/исполнение SQL согласно установленному узлу.
const text = (typeof msg.payload === "string") ? msg.payload : "";
const lines = text.split(/\r?\n/);
const readings = [];
const events = [];

for (const line of lines) {
    let m = line.match(/^DATA\s+n=(\d+)\s+s1=(-?\d+(?:\.\d+)?)\s+s2=(-?\d+(?:\.\d+)?)\s+s3=(\d+)/);
    if (m) {
        const n = Number(m[1]), s1 = Number(m[2]), s2 = Number(m[3]), s3 = Number(m[4]);
        const t = n * 3;
        const vals = [
            ["s1", s1, 0, 80],
            ["s2", s2, 2, 400],
            ["s3", s3, 0, 1]
        ];
        for (const [sensor, value, min, max] of vals) {
            if (!Number.isFinite(value) || value < min || value > max) {
                events.push({n, t_s:t, type:"FAULT", message:`${sensor}: значение ${value} вне диапазона ${min}..${max}`});
            } else {
                readings.push({n, t_s:t, sensor, value});
            }
        }
        continue;
    }
    m = line.match(/^EVENT\s+n=(\d+)\s+type=(THRESHOLD|NORMAL)$/);
    if (m) {
        const n = Number(m[1]);
        events.push({n, t_s:n*3, type:m[2], message:null});
    }
}

// Формируем массив объектов. В реальном flow следующий узел должен безопасно
// параметризовать SQL, а не конкатенировать непроверенные строки.
msg.payload = {readings, events};
return [ {payload: readings}, {payload: events} ];
