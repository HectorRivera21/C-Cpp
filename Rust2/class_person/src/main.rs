#[derive(Debug)]
#[allow(dead_code)]
struct Person<T, U> {
    name: T,
    age: U,
}

fn main() {
    let person1 = Person {
        name: "hector",
        age: 21,
    };

    println!("person1: {:?}", person1);
}
