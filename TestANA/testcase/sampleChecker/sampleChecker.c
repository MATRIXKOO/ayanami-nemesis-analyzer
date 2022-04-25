int main();

void caller()
{
  main();  // expected-warning {{call to main}}
}