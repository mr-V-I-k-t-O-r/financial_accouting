# automated information system for financial accounting of the enterprise

this AIS was created like coursework in my university.
files was created by QT creator, i`m not replaced it for ability to build project

---

## this application need connection to database PostgreSQL(DataBase name, user name and password for user you need to change in file 'mainwindow.cpp')

### DataBase, which you use need have that tables:

* accounts
	* id - bigint(PK, autoincriment)
	* name - text
	* summ - float
* employees
	* id - bigint(PK, autoincriment)
	* first_name - text
	* last_name - text
	* middle_name - text(optional)
	* pass_batch - bigint
	* pass_number - bigint
	* city - text
	* street - text
	* house - text
	* flat - bigint(optional)
	* inn - varchar(12)
	* post - bigint
* operation_types
	* id - bigint(PK, autoincriment)
	* name - text
	* income - bool
* operations
	* id - bigint(PK, autoincriment)
	* summ - float
	* date - date
	* account_id - bigint
	* subject_id - bigint
	* employee_id - bigint
	* operation_type - bigint
	* person_id - bigint
	* organization_id - bigint
* organizations
	* id - bigint(PK, autoincriment)
	* name - text
	* city - text
	* street - text
	* house - text
	* flat - bigint(optional)
	* account_number - varchar(20)
	* inn - varchar(10)
* persons
	* id - bigint(PK, autoincriment)
	* first_name - text
	* last_name - text
	* middle_name - text(optional)
	* pass_batch - bigint
	* pass_number - bigint
	* city - text
	* street - text
	* house - text
	* flat - bigint(optional)
	* inn - varchar(12)
* posts
	* id - bigint(PK, autoincriment)
	* name - text
* subjects
	* id - bigint(PK, autoincriment)
	* name - text
---
For use this application you need to add posts for your employees, employees who has access to finances of the enterprise, your clients(persons or other enterprises), your providers(person or other enterprises), subjects of contracts with people or other enterprises, accounts which uses in your enterprise, operation types which you use and finaly finance operations.
When you will add an operation, application will change balance on account which used by this operation, guided by income of operation type which used in this operation.

You can see report of your financial accounting by click '' button and choose time-interval. Report includes number of income operations which was in this interval, finance change by income operations, number of expense operations which was in this interval, finance change by expense operations, total number of operations and total finance change by all operations.