fn concat_strings(s1: &String, s2: &String) -> String { 
    format!("{s1}{s2}")
}
fn clone_and_modify(s: &String) -> String {
        // Your code here
    let clone_string = s.clone();
    format!("{clone_string}World!")
}
#[allow(unused_variables, unused_mut)]
fn sum(total: &mut i32, low: i32, high: i32) {
    // Write your code here!
    for i in low..=high{
        *total += i;
    }
    
}

fn main() { 
    let s1 = String::from("Hello, "); 
    let s2 = String::from("World!"); 
    let result = concat_strings(&s1, &s2); 
    println!("{}", result);
    /////////////////////////////////
    // problem 2 

    let s = String::from("Hello, ");
    let modified = clone_and_modify(&s);
    println!("Original: {}", s); // Should print: "Original: Hello, "
    println!("Modified: {}", modified); // Should print: "Modified: Hello, World!"
    let mut total = 0;
    let low = 0;
    let high = 100;

    sum(&mut total, low, high);
    println!("The sum from {} to {} is: {}", low, high, total);

}
