fn foo(strs: Vec<String>) -> String {
    strs.into_iter()
        .reduce(|a, b| {
            a.chars()
                .zip(b.chars())
                .take_while(|(c, d)| c == d)
                .map(|(x, _)| x)
                .collect()
        })
        .unwrap()
}

fn main() {
    let strs: Vec<String> = ["flow", "flower", "flew"].map(String::from).to_vec();
    println!("{}",foo(strs));
}
