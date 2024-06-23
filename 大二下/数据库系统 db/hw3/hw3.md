# database system hw3

3200105872 庄毅非

##### 3.8 Consider the bank database of Figure 3.18, where the primary keys are underlined. Construct the following SQL queries for this relational database

a. Find the ID of each customer of the bank who has an account but not a loan.

```sql
select ID from depositor
where ID not in(
    select ID from borrower
);
```

b. Find the ID of each customer who lives on the same street and in the same city as customer '12345'.
```sql
select d.ID from customer as d
where (customer_street,customer_city) = (
	select customer_street,customer_city from customer as c where c.ID = 12345;
)
```
c. Find the name of each branch that has at least one customer who has an account in the bank and who lives in “Harrison”.
```sql
select distinct
    branch_name
from account,
(
    select account_number
    from depositor as d,
    (select ID from customer where customer_city = 'Harrison') as e
    where d.ID = e.ID
) as c
where account.account_number = c.account_number
```
##### 3.9 Consider the relational database of Figure 3.19, where the primary keysare underlined. Give an expression in SQL for each of the following queries.
a.  Find the ID, name, and city of residence of each employee who works for “First Bank Corporation”.
```sql
select ID, name, city
from employee,
(select ID from works where company_name = 'First Bank Corporation') as c
where employee.ID = c.ID;
```
b. Find the ID, name, and city of residence of each employee who works for “First Bank Corporation” and earns more than $10000.
```sql
select ID, person_name, city
from employee,
(
    select ID
    from works
    where company = "First Bank Corporation"
          and salary > 10000
) as q
where employee.ID = q.ID;
```
c. Find the ID of each employee who does not work for “First Bank Corporation”.
```sql
select ID
from employee
where ID not in (
    select ID from works where company_name = 'First Bank Corpo-ration');
```

d. Find the ID of each employee who earns more than every employee of “Small Bank Corporation”.

```sql
select ID
from works
where salary>all
(
    select salary from works where company_name = "Small BankCorporation"
);
```

e. Assume that companies may be located in several cities. Find the name of each company that is located in every city in which “Small Bank Corporation” is located.

```sql
select company_name
from company as c
where not exists
(
    (select city
     from comapny as a
     where a.company_name = 'SmallBank Corporation')
    except
    (select city
     from company as b
     where b.company_name = c.company_name)
);
```

f. Find the name of the company that has the most employees (or companies, in the case where there is a tie for the most).

```sql
select company_name
from works
group by works
having count(distinct ID) >=all
(
    select count(distinct ID) from works group by (company_name)
);
```

g. Find the name of each company whose employees earn a higher salary, on average, than the average salary at “First Bank Corporation”.

```sql
select company_name
from works
group by company_name
having avg（salary） >
(
    select avg(salary) as base
    from works
    where company_name = 'First Bank Corporation'
);
```

##### 3.10 Consider the relational database of Figure 3.19. Give an expression in SQL for each of the following:

a. Modify the database so that the employee whose ID is '12345' now lives in “Newtown”.

```sql
update employee 
set city ="Newtown" 
where ID ='12345';
```

b. Give each manager of “First Bank Corporation” a 10 percent raise unless the salary becomes greater than $100000; in such cases, give only a 3 percent raise

```sql
update works
set salary = (case
                  when salary > 100000 then
                      salary * 1.03
                  else
                      salary * 1.1
              end
             )
where works.ID in (
                      select works.ID from works, manages where works.ID = manages.manager_id
                  )
```

##### 3.11 Write the following queries in SQL, using the university schema.

a. Find the ID and name of each student who has taken at least one Comp. Sci. course; make sure there are no duplicate names in the result

```sql
SELECT DISTINCT name
FROM takes
JOIN
  (SELECT course_id
   FROM course
   WHERE dept_name = 'Comp. Sci.' )
JOIN student;
```

b. Find the ID and name of each student who has not taken any course offered before 2017.

```sql
SELECT ID, name
FROM student
WHERE ID NOT IN 
    (SELECT ID
    FROM takes
    WHERE YEAR<2017);
```

c. For each department, find the maximum salary of instructors in that department. You may assume that every department has at least one instructor.

```sql
SELECT Max(salary),
         dept_name
FROM instructor
JOIN department
GROUP BY  dept_name; 
```

d. Find the lowest, across all departments, of the per-department maximum salary computed by the preceding query.

```sql
SELECT min(topsalary),
        dept_name from
    (SELECT max(salary) as topsalary,
        dept_name
    FROM instructor
    JOIN department
    GROUP BY dept_name);
```



3.15 Consider the bank database of Figure 3.18, where the primary keys are underlined. Construct the following SQL queries for this relational database.

a. Find each customer who has an account at  every branch located in “Brooklyn”.

```sql
SELECT *
FROM customer AS c
WHERE NOT exists(
    (SELECT branch_name
    FROM branch
    WHERE city ="Brooklyn";) 
    except
    (SELECT branch_name
     FROM account
     WHERE account_number IN 
     (SELECT account_number
      FROM depositor AS d
      WHERE d.ID= c.ID;)))
```

b. Find the total sum of all loan amounts in the bank.

```sql
select sum(amount),branch_name
from loan
group by branch_name
```

c. Find the names of all branches that have assets greater than those of at least one branch located in “Brooklyn”.

```sql
select branch_name from branch
where branch.assets > some(
	select assets from branch where branch_city = "Brooklyn"
);
```



















