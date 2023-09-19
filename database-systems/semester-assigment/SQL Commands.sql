*CREATING TABLES*

CREATE TABLE Staff(
    id NUMBER(8,0) NOT NULL PRIMARY KEY,
    first_name VARCHAR(255) NOT NULL,
    last_name VARCHAR(255) NOT NULL,
    phone_number VARCHAR(255) NOT NULL,
    birth_year NUMBER(4,0) NOT NULL,
    birth_month NUMBER(2,0) NOT NULL,
    birth_day NUMBER(2,0) NOT NULL
);

CREATE TABLE Student(
    id NUMBER(8,0) NOT NULL PRIMARY KEY,
    first_name VARCHAR(255) NOT NULL,
    last_name VARCHAR(255) NOT NULL,
    address_postal_code VARCHAR(255) NOT NULL,
    address_city VARCHAR(255) NOT NULL,
    address_street VARCHAR(255) NOT NULL,
    address_number VARCHAR(255) NOT NULL,
    birth_year NUMBER(4,0) NOT NULL,
    birth_month NUMBER(2,0) NOT NULL,
    birth_day NUMBER(2,0) NOT NULL,
    staff_id NUMBER(8,0) NOT NULL,
    FOREIGN KEY (staff_id) REFERENCES Staff(id)
);

CREATE TABLE  Publisher(
    id NUMBER(1,0) NOT NULL PRIMARY KEY,
    name VARCHAR(255) NOT NULL
);

CREATE TABLE Authentication_System(
    staff_id NUMBER(8,0) NOT NULL PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    password VARCHAR(255) NOT NULL,
    FOREIGN KEY(staff_id) REFERENCES Staff(id)
);

CREATE TABLE Student_email(
    id NUMBER(8,0) NOT NULL PRIMARY KEY,
    student_id NUMBER(8,0) NOT NULL,
    email VARCHAR(255),
    FOREIGN KEY(student_id) REFERENCES Student(id)
);

CREATE TABLE Student_phone_number(
    id NUMBER(8,0) NOT NULL PRIMARY KEY,
    student_id NUMBER(8,0) NOT NULL,
    phone_number VARCHAR(255) NOT NULL,
    FOREIGN KEY(student_id) REFERENCES Student(id)
);

CREATE TABLE Book(
    isbn VARCHAR(255) NOT NULL PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    author VARCHAR(255) NOT NULL,
    category VARCHAR(255) NOT NULL,
    edition VARCHAR(255) NOT NULL,
    publication_date date NOT NULL,
    price INT NOT NULL,
    reserve_date date,
    return_date date,
    student_id NUMBER(8,0),
    publisher_id NUMBER(1,0) NOT NULL,
    FOREIGN KEY(student_id) REFERENCES Student(id),
    FOREIGN KEY(publisher_id) REFERENCES Publisher(id)
);

*Filling Tables*

INSERT INTO Staff VALUES(50690781, 'Bairrfhionn', 'Pethes', '505-466-7940', 1995, 09, 06);
INSERT INTO Staff VALUES(98017604, 'Axel', 'Nieri', '615-258-7302', 1968, 04, 16);
INSERT INTO Staff VALUES(73267121, 'Red', 'Lowe', '715-993-3449', 1982, 04, 27);
INSERT INTO Staff VALUES(26991745, 'Jelena', 'Kearney', '606-857-8284', 1953, 10, 01);
INSERT INTO Staff VALUES(37065937, 'Jockel', 'Lu', '321-967-3130', 1979, 12, 30);
INSERT INTO Staff VALUES(62144889, 'Dorota', 'Miyamoto', '978-674-7536', 1949, 09, 29);
INSERT INTO Staff VALUES(25187152, 'Sverrir', 'Gerhard', '303-892-6655', 1980, 11, 22);
INSERT INTO Staff VALUES(67721272, 'Hadia', 'Dimov', '912-577-8349', 1989, 02, 08);
INSERT INTO Staff VALUES(74860600, 'Philomena', 'Polzin', '762-999-7366', 1982, 08, 13);
INSERT INTO Staff VALUES(03952198, 'Paskal', 'Romeijn', '937-895-5924', 1989, 01, 27);

INSERT INTO Student VALUES(94391307, 'Emma', 'Bohemia', 10032, 'New-York', 'Peter Lane', '3', 2006, 2,  1, 50690781);
INSERT INTO Student VALUES(69843606, 'Robin', 'Baptista', 19104, 'Philadelphia', 'Culford Road', '13', 2005, 2, 3, 37065937);
INSERT INTO Student VALUES(02616773, 'Scout', 'Bela', 06511, 'Philadelphia', 'Culford Road', '12', 2002, 9, 10, 37065937);
INSERT INTO Student VALUES(20773218, 'Taylor', 'Akashiya', 19104, 'Philadelphia', 'Renfrew Court', '74', 2002, 10, 21, 73267121);
INSERT INTO Student VALUES(28995536, 'Sarah', 'Rachimova', 19104, 'New Haven', 'Knight Street', '64', 2006, 2, 10, 98017604);
INSERT INTO Student VALUES(10332608, 'Juno', 'Rambova', 19104, 'Philadelphia', 'Jura Street', '12', 2003, 9, 3, 37065937);
INSERT INTO Student VALUES(84278077, 'Delmira', 'Galena', 10032, 'Philadelphia', 'Watt Crescent', '2', 2002, 4, 15, 67721272);
INSERT INTO Student VALUES(99983876, 'Coral', 'Rivera', 06511, 'New-York', 'Vine Place', '86', 2001, 5, 21, 98017604);
INSERT INTO Student VALUES(73748167, 'Juniper', 'Westenra', 10038, 'New Haven', 'Welton Road', '7', 2008, 1, 28, 26991745);
INSERT INTO Student VALUES(70841066, 'Maria', 'Tesla', 10032, 'New-York', 'Streatfield Road', '36', 2003, 5, 15, 74860600);
INSERT INTO Student VALUES(04672687, 'Ophelia', 'Borba', 06511, 'New-York', 'Thomas Place', '96', 2008, 11, 28, 37065937);
INSERT INTO Student VALUES(47832063, 'Christina', 'Luna', 10038, 'New Haven', 'Tanyard Lane', '12', 2008, 1, 1, 67721272);
INSERT INTO Student VALUES(80648724, 'Mala', 'Varga', 06511, 'New-York', 'Walmer Street', '62', 2005, 11, 29, 62144889);
INSERT INTO Student VALUES(26327979, 'Lennox', 'Ozera', 19104, 'New Haven', 'Heol Mabon', '1', 2001, 12, 3, 25187152);
INSERT INTO Student VALUES(92983336, 'Katharine', 'Touya', 06511, 'Philadelphia', 'Pentland Avenue', '8', 2005, 3, 25, 03952198);
INSERT INTO Student VALUES(64499208, 'Evan', 'Bela', 10038, 'New Haven', 'Medway Drive', '92', 2006, 1, 15, 03952198);
INSERT INTO Student VALUES(59281797, 'Paige', 'Dracula', 06511, 'New-York', 'Burdale Close', '28', 2003, 2, 25, 37065937);
INSERT INTO Student VALUES(31805808, 'Helen', 'Petrova', 10038, 'New Haven', 'Wembley Way', '54', 2001, 8, 21, 73267121);
INSERT INTO Student VALUES(08735418, 'Gabriela', 'Kamura', 19104, 'New-York', 'Castle Gate', '72', 2006, 4, 10, 25187152);
INSERT INTO Student VALUES(65182451, 'Cordelia', 'Fangula', 19104, 'Philadelphia', 'Beckett Close', '64', 2004, 8, 21, 50690781);

INSERT INTO Publisher VALUES(1, 'Penguin/Random House');
INSERT INTO Publisher VALUES(2, 'Hachette Book Group');
INSERT INTO Publisher VALUES(3, 'Harper Collins');
INSERT INTO Publisher VALUES(4, 'Simon and Schuster');
INSERT INTO Publisher VALUES(5, 'Macmillan');

INSERT INTO Authentication_System VALUES(50690781, 'ecometha', 'QzXOwRMgLe');
INSERT INTO Authentication_System VALUES(98017604, 'ropotewi', '8gf72Ekxon');
INSERT INTO Authentication_System VALUES(73267121, 'toeltale', '8gf72Ekxon');
INSERT INTO Authentication_System VALUES(26991745, 'uententr', 'lzD4QhMK0Q');
INSERT INTO Authentication_System VALUES(37065937, 'nderesel', 'wAnQKZXiV4');
INSERT INTO Authentication_System VALUES(62144889, 'iathorpi', 'wAnQKZXiV4');
INSERT INTO Authentication_System VALUES(25187152, 'icestica', '5SiImEZj0g');
INSERT INTO Authentication_System VALUES(67721272, 'devirerp', 'FuHVyjbDbx');
INSERT INTO Authentication_System VALUES(74860600, 'rtsectra', 'rV96E11nch');
INSERT INTO Authentication_System VALUES(03952198, 'shcolard', 'bgEVEREROC');

INSERT INTO Student_email VALUES(1, 94391307, 'fmKrFRfrJo@gmail.com');
INSERT INTO Student_email VALUES(2, 69843606, 'Ke8bSO8xJo@gmail.com');
INSERT INTO Student_email VALUES(3, 02616773, 'TxdFVjWXHK@gmail.com');
INSERT INTO Student_email VALUES(4, 20773218, 'BWI3DMvVF6@gmail.com');
INSERT INTO Student_email VALUES(5, 28995536, 'tAfWp4C1N8@gmail.com');
INSERT INTO Student_email VALUES(6, 10332608, 'ujcfHfkegg@gmail.com');
INSERT INTO Student_email VALUES(7, 84278077, 'goKdJ7kXSx@gmail.com');
INSERT INTO Student_email VALUES(8, 99983876, 'Q17kOwPH7Z@gmail.com');
INSERT INTO Student_email VALUES(9, 73748167, 'EX6FAsnOf5@gmail.com');
INSERT INTO Student_email VALUES(10, 70841066, 'oMD2gTGSf9@gmail.com');
INSERT INTO Student_email VALUES(11, 04672687, 'TjPeYhPrTP@gmail.com');
INSERT INTO Student_email VALUES(12, 47832063, 'N4zgq2fZTL@gmail.com');
INSERT INTO Student_email VALUES(13, 80648724, '4iWDLFLKJu@gmail.com');
INSERT INTO Student_email VALUES(14, 26327979, 'VePFXSgq1e@gmail.com');
INSERT INTO Student_email VALUES(15, 92983336, '4NwjmA01p0@gmail.com');
INSERT INTO Student_email VALUES(16, 64499208, '2q6xQ1zdov@gmail.com');
INSERT INTO Student_email VALUES(17, 59281797, 'tw4mTmT423@gmail.com');
INSERT INTO Student_email VALUES(18, 31805808, 'A2uJz7SSS0@gmail.com');
INSERT INTO Student_email VALUES(19, 08735418, 'eYG22zA8Nf@gmail.com');
INSERT INTO Student_email VALUES(20, 65182451, 'qPu030IVhz@gmail.com');

INSERT INTO Student_phone_number VALUES(1, 94391307, '571-776-6905');
INSERT INTO Student_phone_number VALUES(2, 69843606, '347-358-2804');
INSERT INTO Student_phone_number VALUES(3, 02616773, '707-742-7237');
INSERT INTO Student_phone_number VALUES(4, 20773218, '931-857-7183');
INSERT INTO Student_phone_number VALUES(5, 28995536, '859-984-9114');
INSERT INTO Student_phone_number VALUES(6, 10332608, '903-854-4626');
INSERT INTO Student_phone_number VALUES(7, 84278077, '202-396-6060');
INSERT INTO Student_phone_number VALUES(8, 99983876, '731-637-8743');
INSERT INTO Student_phone_number VALUES(9, 73748167, '325-525-9577');
INSERT INTO Student_phone_number VALUES(10, 70841066, '540-756-7873');
INSERT INTO Student_phone_number VALUES(11, 04672687, '925-696-8735');
INSERT INTO Student_phone_number VALUES(12, 47832063, '775-656-9761');
INSERT INTO Student_phone_number VALUES(13, 80648724, '580-825-7449');
INSERT INTO Student_phone_number VALUES(14, 26327979, '561-677-6117');
INSERT INTO Student_phone_number VALUES(15, 92983336, '701-625-9435');
INSERT INTO Student_phone_number VALUES(16, 64499208, '412-939-1279');
INSERT INTO Student_phone_number VALUES(17, 59281797, '681-597-9658');
INSERT INTO Student_phone_number VALUES(18, 31805808, '848-348-1257');
INSERT INTO Student_phone_number VALUES(19, 08735418, '562-884-7007');
INSERT INTO Student_phone_number VALUES(20, 65182451, '802-224-2705');

INSERT INTO Book VALUES('9781234567897', 'Game of wind', 'Julia Black', 'Horror', 'first', TO_DATE('23/2/2016', 'dd/mm/yyyy'), 4500, TO_DATE('4/3/2022', 'dd/mm/yyyy'), TO_DATE('4/6/2022', 'dd/mm/yyyy'), 69843606, 1);
INSERT INTO Book VALUES('3233079183270', 'Game of wind', 'Julia Black', 'Horror', 'first', TO_DATE('23/2/2016', 'dd/mm/yyyy'), 4500, TO_DATE('6/1/2022', 'dd/mm/yyyy'), TO_DATE('6/4/2022', 'dd/mm/yyyy'), 94391307, 3);
INSERT INTO Book VALUES('7429246883063', 'Game of wind', 'Julia Black', 'Horror', 'first', TO_DATE('23/2/2016', 'dd/mm/yyyy'), 4500, TO_DATE('24/3/2022', 'dd/mm/yyyy'), TO_DATE('24/6/2022', 'dd/mm/yyyy'), 84278077, 2);
INSERT INTO Book VALUES('4772525397681', 'Game of wind', 'Julia Black', 'Horror', 'first', TO_DATE('23/2/2016', 'dd/mm/yyyy'), 6500, TO_DATE('15/2/2022', 'dd/mm/yyyy'), TO_DATE('15/5/2022', 'dd/mm/yyyy'), 28995536, 3);
INSERT INTO Book VALUES('5929340550576', 'Vultures and wives', 'Sandy Gibson', 'Comedy', 'third', TO_DATE('2/6/2015', 'dd/mm/yyyy'), 6500, TO_DATE('2/4/2022', 'dd/mm/yyyy'), TO_DATE('2/7/2022', 'dd/mm/yyyy'), 73748167, 5);
INSERT INTO Book VALUES('8260624469622', 'Vultures and wives', 'Sandy Gibson', 'Comedy', 'third', TO_DATE('2/6/2015', 'dd/mm/yyyy'), 6500, TO_DATE('5/1/2022', 'dd/mm/yyyy'), TO_DATE('5/4/2022', 'dd/mm/yyyy'), 94391307, 3);
INSERT INTO Book VALUES('8902604904880', 'Foe of time', 'Scout Medina', 'Sci-fy', 'fourth', TO_DATE('7/8/2016', 'dd/mm/yyyy'), 3500, TO_DATE('17/4/2022', 'dd/mm/yyyy'), TO_DATE('17/7/2022', 'dd/mm/yyyy'), 04672687, 4);
INSERT INTO Book VALUES('4611192948712', 'Foe of time', 'Scout Medina', 'Sci-fy', 'fourth', TO_DATE('7/8/2016', 'dd/mm/yyyy'), 3500, TO_DATE('26/2/2022', 'dd/mm/yyyy'), TO_DATE('26/5/2022', 'dd/mm/yyyy'), 20773218, 1);
INSERT INTO Book VALUES('3592465318824', 'Foe of time', 'Scout Medina', 'Sci-fy', 'fourth', TO_DATE('7/8/2016', 'dd/mm/yyyy'), 3500, TO_DATE('22/1/2022', 'dd/mm/yyyy'), TO_DATE('22/4/2022', 'dd/mm/yyyy'), 84278077, 2);
INSERT INTO Book VALUES('7235874228698', 'Humans of the great', 'Chawki Robinson', 'Comedy', 'second', TO_DATE('25/11/2018', 'dd/mm/yyyy'), 2500, TO_DATE('21/4/2022', 'dd/mm/yyyy'), TO_DATE('21/7/2022', 'dd/mm/yyyy'), 02616773, 4);
INSERT INTO Book VALUES('5476316844118', 'Humans of the great', 'Chawki Robinson', 'Comedy', 'second', TO_DATE('25/11/2018', 'dd/mm/yyyy'), 2500, TO_DATE('14/4/2022', 'dd/mm/yyyy'), TO_DATE('14/7/2022', 'dd/mm/yyyy'), 99983876, 5);
INSERT INTO Book VALUES('7958312473140', 'Humans of the great', 'Chawki Robinson', 'Comedy', 'second', TO_DATE('25/11/2018', 'dd/mm/yyyy'), 2500, TO_DATE('8/2/2022', 'dd/mm/yyyy'), TO_DATE('8/5/2022', 'dd/mm/yyyy'), 10332608, 1);
INSERT INTO Book VALUES('8638598057358', 'Robots and giants', 'Scout Medina', 'Sci-fy', 'fourth', TO_DATE('15/1/2017', 'dd/mm/yyyy'), 4000, TO_DATE('23/1/2022', 'dd/mm/yyyy'), TO_DATE('23/4/2022', 'dd/mm/yyyy'), 47832063, 3);
INSERT INTO Book VALUES('7182933668474', 'Robots and giants', 'Scout Medina', 'Sci-fy', 'fourth', TO_DATE('15/1/2017', 'dd/mm/yyyy'), 4000, TO_DATE('12/1/2022', 'dd/mm/yyyy'), TO_DATE('12/4/2022', 'dd/mm/yyyy'), 70841066, 4);
INSERT INTO Book(isbn, title, author, category, edition, publication_date, price, publisher_id) VALUES('3106074063162', 'Fefender of dawn', 'Travis Gonzales', 'Adcenture', 'first', TO_DATE('26/5/2016', 'dd/mm/yyyy'), 6000, 2);
INSERT INTO Book(isbn, title, author, category, edition, publication_date, price, publisher_id) VALUES('2374274135147', 'Fefender of dawn', 'Travis Gonzales', 'Adcenture', 'first', TO_DATE('26/5/2016', 'dd/mm/yyyy'), 6000, 4);
INSERT INTO Book(isbn, title, author, category, edition, publication_date, price, publisher_id) VALUES('5710020766517', 'Fefender of dawn', 'Travis Gonzales', 'Adcenture', 'first', TO_DATE('26/5/2016', 'dd/mm/yyyy'), 6000, 2);
INSERT INTO Book(isbn, title, author, category, edition, publication_date, price, publisher_id) VALUES('0021606268275', 'Fefender of dawn', 'Travis Gonzales', 'Adcenture', 'first', TO_DATE('26/5/2016', 'dd/mm/yyyy'), 6000, 5);
INSERT INTO Book(isbn, title, author, category, edition, publication_date, price, publisher_id) VALUES('7578812744004', 'Witch of the sea', 'Steve Perry', 'Horror', 'third', TO_DATE('8/6/2013', 'dd/mm/yyyy'), 3500, 2);
INSERT INTO Book(isbn, title, author, category, edition, publication_date, price, publisher_id) VALUES('7740517963890', 'Witch of the sea', 'Steve Perry', 'Horror', 'third', TO_DATE('8/6/2013', 'dd/mm/yyyy'), 3500, 1);

*Update*
*Updates the wrong book title in the book table*
UPDATE Book SET Book.title = 'Defender of dawn' WHERE Book.title = 'Fefender of dawn';

*Update the wrong book category in the book table*
UPDATE Book SET category='Adventure' WHERE category='Adcenture';

*Update edition*
UPDATE Book SET edition='First' WHERE category='first';


*Alter*
*Adds the non mandatory foundation date for each publisher*
ALTER TABLE Publisher ADD founding_date date;

*Alter books isbn to int*
ALTER TABLE Book MODIFY (isbn INT); 


*Select*

*Which students reserved the book titled: Game of wind?*
SELECT Student.first_name, Student.last_name FROM Student JOIN Book ON Student.id = Book.student_id WHERE Book.title = 'Game of wind';

*How many students does each staff member handle?*
SELECT Staff.id, COUNT(Student.id) FROM Staff JOIN Student ON Staff.id = Student.staff_id GROUP BY Staff.id;

*Distinct books in library and how many of each?*
Select Book.title, COUNT(Book.title) FROM Book GROUP BY Book.title;

*Not reserved books.*
Select Book.isbn, Book.title FROM Book WHERE Book.reserve_date IS NULL;

*How many books are resereved by each student*
SELECT Book.student_id, COUNT(*) "Number of Books" FROM Book GROUP BY Book.student_id;

*Number of books of each publisher*
SELECT Publisher.name, COUNT(Book.publisher_id) FROM Publisher JOIN Book ON Publisher.id = Book.publisher_id GROUP BY Publisher.name;

*Not reserved books with adventure category*
SELECT Book.isbn, Book.title FROM Book WHERE Book.reserve_date IS NULL AND Book.category = 'Adventure';

*Students older than 18*
SELECT Student.first_name, Student.last_name, Student.birth_year FROM Student WHERE Student.birth_year < 2004;

*Every Staff member*
SELECT * FROM Staff;

*Every Student*
SELECT * FROM Student;

*Every Book*
SELECT * FROM Book;

*Every book with category: horror*
SELECT * FROM Book WHERE category='Horror';

*Staffs username and password*
SELECT Staff.first_name, Staff.last_name, Authentication_system.username, Authentication_system.password FROM Staff JOIN Authentication_system ON Staff.id = Authentication_system.staff_id;

*WHo Reserved most expensive books*
SELECT Book.student_id FROM BOOK WHERE price = (SELECT Max(Book.price) FROM Book)