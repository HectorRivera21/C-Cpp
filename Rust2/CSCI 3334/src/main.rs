use std::collections::HashMap;
pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    let mut hash_map = HashMap::new();

   for (i, &value) in  nums.iter().enumerate(){
       if let Some(&j) = hash_map.get(&(target-value)){
           return vec![j as i32, i as i32];
       }
       hash_map.insert(value,i);
   }
   vec![-1,-1]
}
pub fn is_palindrome(x: i32) -> bool {
    if x < 0{
        return false
    }
    let mut n = x;
    let mut reverse : i32 = 0;
    while n != 0{
        reverse = (reverse*10)+(n%10);
        n/=10;
    }
   reverse == x
}
pub fn roman_to_int(s: String) -> i32 {
    let mut sum = 0;
    let map = HashMap::from([
        ('I', 1),
        ('V', 5),
        ('X', 10),
        ('L', 50),
        ('C', 100),
        ('D', 500),
        ('M', 1000),
    ]);
    let mut prev_val = 0;
    for c in s.chars() {
        if let Some(&val) = map.get(&c) {
            if prev_val < val {
                sum -= 2 * prev_val;
            }
            sum += val;
            prev_val = val;
        }
    }
    sum
}
pub fn longest_common_prefix(strs: Vec<String>) -> String {
        
    let mut strs = strs;
   if strs.len() == 0 {return "".to_string()};

    let mut prefix = strs.pop().unwrap();

    for word in strs.iter_mut() {
        while prefix.len() != 0 {
            if word.starts_with(&prefix) {
                break
            } else { 
                prefix.pop(); 
            }
        }
    }

    prefix 
}
pub fn is_valid(s: String) -> bool {
    let mut n: Vec<char> = Vec::new();

    for (_i , val) in s.chars().enumerate(){
        if val == '(' || val== '[' || val == '{'{
            n.push(val);
        }
        else{
            if n.is_empty() || (val as u8 - n[n.len()-1] as u8) > 2 as u8{
                return false
            }
            else{
                n.pop();
            }
        }
    }

    n.is_empty()
}

#[allow(non_snake_case)]
mod LL;
use LL::ListNode;

pub fn merge_two_lists(list1: Option<Box<ListNode>>, list2: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    match (list1 , list2){
        (Some(node1), Some(node2)) => {
            if node1.val < node2.val {
                Some(Box::new(ListNode{
                    val: node1.val,
                    next: merge_two_lists(node1.next, Some(node2))
                }))
            }
            else{
                Some(Box::new(ListNode{
                    val: node2.val,
                    next: merge_two_lists(Some(node1), node2.next)
                }))
            }
        },
         (Some(node), None) => Some(node),
         (None, Some(node)) => Some(node),
         _ => None,
    }
}
pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
    let mut j = 1;
    for i in 1..nums.len(){
       if nums[i] != nums[i-1]
       {
           nums[j] = nums[i];
           j+=1;
       }
    }
    j as i32
}
pub fn remove_element(nums: &mut Vec<i32>, val: i32) -> i32 {
    let (mut i, mut n) = (0, nums.len());
    while i<n{
        if nums[i] == val{
            nums.swap_remove(i);
            n-=1;
        }
        else{
            i+=1;
        }
    }
    n as i32
}
pub fn str_str(s1: String, s2: String) -> i32 {
    let n = s2.len();
    let s1 = s1.as_bytes();
    let s2 = s2.as_bytes();
    let mut window = s1.windows(n);
    match window.position(|x|x == s2){
        Some(x)=> x as i32,
        _=> -1 as i32
    } 
}
pub fn search_insert(nums: Vec<i32>, target: i32) -> i32 {
    let mut start: usize = 0;
    let mut end: usize = nums.len();
    while start<end{
        let mid: usize = start + ((end - start) >> 1);
        if nums[mid] == target{
            start = mid;
            break;
        }
        else if nums[mid] > target{
            end = mid;
        }
        else 
        {
            start = mid + 1;
        }
    }
    start as i32
}
fn main(){
    str_str("sadbutsad".to_string(),"sad".to_string());
}

#[cfg(test)]
mod tests{
    use super::*;
    #[test]
    fn test_two_sum() {
        assert_eq!(two_sum(vec![2, 7, 11, 15], 9), vec![0, 1]);
    }

    #[test]
    fn test_is_palindrome() {
        assert_eq!(is_palindrome(121), true);
        assert_eq!(is_palindrome(-121), false);
    }

    #[test]
    fn test_roman_to_int() {
        assert_eq!(roman_to_int("III".to_string()), 3);
        assert_eq!(roman_to_int("IV".to_string()), 4);
    }

    #[test]
    fn test_longest_common_prefix() {
        assert_eq!(longest_common_prefix(vec!["flower".to_string(), "flow".to_string(), "flight".to_string()]), "fl".to_string());
        assert_eq!(longest_common_prefix(vec!["dog".to_string(), "racecar".to_string(), "car".to_string()]), "".to_string());
    }

    #[test]
    fn test_is_valid() {
        assert_eq!(is_valid("()".to_string()), true);
        assert_eq!(is_valid("()[]{}".to_string()), true);
        assert_eq!(is_valid("(]".to_string()), false);
    }

    fn to_list(vec: Vec<i32>) -> Option<Box<ListNode>> {
        let mut current = None;
        for &v in vec.iter().rev() {
            let mut node = ListNode::new(v);
            node.next = current;
            current = Some(Box::new(node));
        }
        current
    }

    fn to_vec(mut list: Option<Box<ListNode>>) -> Vec<i32> {
        let mut vec = Vec::new();
        while let Some(mut node) = list {
            vec.push(node.val);
            list = node.next.take();
        }
        vec
    }
    #[test]
    fn test_merge_sorted_list(){
        let list1 = to_list(vec![1, 2, 4]);
        let list2 = to_list(vec![1, 3, 4]);
        let merged = merge_two_lists(list1, list2);
        assert_eq!(to_vec(merged), vec![1, 1, 2, 3, 4, 4]);

    }

    #[test]
    fn test_remove_duplicates() {
        let mut nums = vec![1,1,2];
        assert_eq!(remove_duplicates(&mut nums), 2);
    }

    #[test]
    fn test_remove_element() {
        let mut nums = vec![3,2,2,3];
        assert_eq!(remove_element(&mut nums, 3), 2);
    }

    #[test]
    fn test_str_str() {
        assert_eq!(str_str("hello".to_string(), "ll".to_string()), 2);
        assert_eq!(str_str("aaaaa".to_string(), "bba".to_string()), -1);
    }

    #[test]
    fn test_search_insert() {
        assert_eq!(search_insert(vec![1,3,5,6], 5), 2);
        assert_eq!(search_insert(vec![1,3,5,6], 2), 1);
    }
}
