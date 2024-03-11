struct Entry {
    hashtag: String,
    popularity: i32,
}

impl TrendTracker {
    fn new() -> self {
        Vec<Entry> E = Vec::new();
        self
    }
    fn insert(&mut self ,ht: String){
        for i in self.E{
            if i.hashtag == ht {
                return;
            }
        }
        self.E.push(Entry{hashtag: ht, popularity: 0});
    }
    fn size(&mut self) -> i32 {
        self.E.len()
    }
    fn tweeted(&mut self, ht: String){
        for i in self.E{
            if i.hashtag == ht {
                i.popularity += 1;
            }
        }
    }
    fn popularity(&mut self, name: String)-> i32 {
        for i in self.E{
            if i.hashtag == name {
                return i.popularity;
            }
            else
            {
                return -1;
            }
        }
    }
    fn top_trend(&mut self)-> String {
        if self.E.len() == 0 {
            return "".to_string();
        }
        else
        {
            let mut max:Entry;
            for i in self.E{
                if i.popularity > max.popularity {
                    max = i;
                }
            }
            return max.hashtag;
        }
    }
    // Fills the provided vector with the 3 most-tweeted hashtags,
    // in order from most-tweeted to least-tweeted.
    //
    // If there are fewer than 3 hashtags, then the vector is filled
    // with all hashtags (in most-tweeted to least-tweeted order).
    //
    // Must run in O(n) time.    
    fn top_three_trends(&mut self, trend: &mut Vec<String>) {
        use std::collections::BinaryHeap;
        use std::cmp::Reverse;
        if self.E.is_empty() {
            return;
        }
    
        let mut min_heap: BinaryHeap<Reverse<Entry>> = BinaryHeap::new();
    
        for entry in &self.E {
            if min_heap.len() < 3 {
                min_heap.push(Reverse(entry.clone()));
            } else {
                if entry.popularity > min_heap.peek().unwrap().0.popularity {
                    min_heap.pop();
                    min_heap.push(Reverse(entry.clone()));
                }
            }
        }
    
        while let Some(Reverse(entry)) = min_heap.pop() {
            trend.push(entry.hashtag);
        }
    }
    fn remove(&mut self, ht: String){
        for i in self.E{
            if i.hashtag == ht {
                self.E.remove(i);
            }
        }
    }
    // Fills the provided vector with the k most-tweeted hashtags,
    // in order from most-tweeted to least-tweeted.
    //
    // If there are fewer than k hashtags, then the vector is filled
    // with all hashtags (in most-tweeted to least-tweeted order).
    //
    // Must run in O(nk) time.
    fn top_k_trends(&mut self, k: i32, &mut trend: Vec<String>){
        
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_insert() {
        let mut tracker = TrendTracker { E: Vec::new() };
        tracker.insert("test1".to_string());
        assert_eq!(tracker.E.len(), 1);
    }

    #[test]
    fn test_size() {
        let mut tracker = TrendTracker { E: Vec::new() };
        tracker.insert("test1".to_string());
        assert_eq!(tracker.size(), 1);
    }

    #[test]
    fn test_tweeted() {
        let mut tracker = TrendTracker { E: Vec::new() };
        tracker.insert("test1".to_string());
        tracker.tweeted("test1".to_string());
        assert_eq!(tracker.popularity("test1".to_string()), 1);
    }

    // Add tests for other functions here
}