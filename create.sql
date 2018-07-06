DROP TABLE LOC;
DROP TABLE VOIT;
DROP TABLE CLI;
DROP TABLE ID;

CREATE TABLE CLI(
NumCli number(5) CONSTRAINT CLI_PK PRIMARY KEY,
Nom VarChar(20),
Prenom VarChar(20));

CREATE TABLE VOIT(
IdVoit number(5) CONSTRAINT VOIT_PK PRIMARY KEY,
Cat VarChar(2),
Prix number(5));

CREATE TABLE LOC(
IdLoc number(5) CONSTRAINT LOC_PK PRIMARY KEY,
NumCli number(5) CONSTRAINT LOC_REF_CLI REFERENCES CLI,
IdVoit number(20) CONSTRAINT LOC_REF_VOIT REFERENCES VOIT,
DebutLoc VarChar(20),
FinLoc VarChar(20));

CREATE TABLE ID(
Login VarChar(20) CONSTRAINT ID_PK PRIMARY KEY,
Mdp VarChar(20));

insert into CLI values (1,'Journe','Arthur');
insert into CLI values (2,'Rerolle','Pierre-Louis');
insert into CLI values (3,'Federer','Roger');
insert into CLI values (4,'Nadal','Rafael');
insert into CLI values (5,'Martin','Pierre');
insert into CLI values (6,'Dome','Charline');
insert into CLI values (7,'Maison','Marie');
insert into CLI values (8,'Chat','Michel');
insert into CLI values (9,'Thomas','Paul');
insert into CLI values (10,'Maria','Dominique');
insert into VOIT values (1000,'A',100);
insert into VOIT values (1001,'E',450);
insert into VOIT values (1002,'C',75);
insert into VOIT values (1003,'A',100);
insert into VOIT values (1004,'D',200);
insert into VOIT values (1005,'D',200);
insert into VOIT values (1006,'B',300);
insert into VOIT values (1007,'A',100);
insert into VOIT values (1008,'E',450);
insert into VOIT values (1009,'B',300);
insert into LOC values (10000,10,1004, 2018-01-01,2018-01-06);
insert into LOC values (10001,6,1004, 2018-01-01,2018-02-01);
insert into LOC values (10002,4,1000,2018-01-02,2018-02-01);
insert into LOC values (10003,7,1007,2018-01-06,2018-01-08);
insert into LOC values (10004,2,1002,2018-01-06,2018-01-26);
insert into LOC values (10005,9,1008,2018-01-18,2018-02-01);
insert into LOC values (10006,4,1003,2018-01-09,2018-01-19);
insert into LOC values (10007,1,1005,2018-01-01,2018-01-25);
insert into LOC values (10008,3,1009,2018-01-03,2018-01-17);
insert into LOC values (10009,5,1001,2018-01-14,2018-01-21);
insert into ID values ('Journe', 'Maman');
insert into ID values ('Rerolle', 'R3rol1e');
insert into ID values ('Federer','WimBledon2017');
insert into ID values ('Nadal','RgDecima10');
insert into ID values ('Martin','S4l0t');
insert into ID values ('Dome','1990Ch4r');
insert into ID values ('Maison','TielaFamille');
insert into ID values ('Chat','Chi3en');
insert into ID values ('Thomas','papa');
insert into ID values ('Maria','P0l0gne');



