# SimpleAllocationOperatorsChecker

Simple checker that triggers some basic sanity checks when using <i> new </i> and <i> delete </i> operators.

Functionalities:

- Show warning when <i> delete </i> is called on a nullptr
- Show warning when <i> delete </i> is called multiple times on the same memory location
- Show warning when fields or methods are accessed through an instance that has been deallocated with <i> delete </i> operator
- Show warning when objects were instantiated with <i> new </i> operator without calling delete afterwards at some point
- Show warning when there is possibility of calling delete on nullptr (e.g. when nullability isn't checked with if statement)
Based on:<https://github.com/nikk-o/SimpleAllocationOperatorsChecker>
