BEGIN;
DELETE FROM readings;
DELETE FROM events;
DELETE FROM sqlite_sequence WHERE name IN ('readings','events');

INSERT INTO readings(n,t_s,sensor,value) VALUES(1,3,'s1',24.5);
INSERT INTO readings(n,t_s,sensor,value) VALUES(1,3,'s2',61.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(1,3,'s3',0.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(2,6,'s1',35.2);
INSERT INTO readings(n,t_s,sensor,value) VALUES(2,6,'s2',45.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(2,6,'s3',0.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(3,9,'s1',42.1);
INSERT INTO readings(n,t_s,sensor,value) VALUES(3,9,'s2',30.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(3,9,'s3',1.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(4,12,'s1',45.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(4,12,'s2',25.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(4,12,'s3',1.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(5,15,'s1',38.4);
INSERT INTO readings(n,t_s,sensor,value) VALUES(5,15,'s2',50.0);
INSERT INTO readings(n,t_s,sensor,value) VALUES(5,15,'s3',0.0);

INSERT INTO events(n,t_s,type,message) VALUES(3,9,'THRESHOLD','порог температуры');
INSERT INTO events(n,t_s,type,message) VALUES(5,15,'NORMAL','порог температуры');

COMMIT;