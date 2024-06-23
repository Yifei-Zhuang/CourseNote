# Database system exercise 4

3200105872 庄毅非



##### 4.7 Consider the employee database of Figure 4.12. Give an SQL DDL defifinition of this database. Identify referential-integrity constraints that should hold, and include them in the DDL defifinition.

```sql
create table employee(
	ID int primary key,
    person_name varchar(30) not null,
    street varchar(30),
    city varchar(30)
);

create table works(
	ID int primary key,
    company_name varchar(50) not null,
    salary double,
    foreign key(compant_name) references company(company_name)
);

create table company(
	company_name varchar(50) not null,
    city varchar(30)
);

create table manages(
	ID int primary key,
    manager_id int not null,
    foreign key(manager_id) references employee(ID)
)
```



##### 4.9 SQL allows a foreign-key dependency to refer to the same relation, as in the following example:

Answer: If this tuple get deleted, then all employees of this manager , not matter indirectly or directly, will be deleted as well. For the employee_ID is the primary key and manager_ID refer to employee_id of this table, when we delete this tuple, every tuple whose manager_ID is equal to current employee will also be deleted recursively. Finally all employees of this manager , not matter indirectly or directly, will be deleted.



##### 4.12 Suppose a user wants to grant **select** access on a relation to another user. Why should the user include (or not include) the clause **granted by current role** in the **grant** statement?

Answer: In both case the granted user will get the select privilege on that table. But if we auth that user by current role, then even we deprecate current user's account, the authorization will persist. If we auth that user by current account, then if we deprecate current user's account, user been authorized will no longer own select permission on that table.























