pub struct TrendTracker
{
    #[allow(non_snake_case)]
    pub e: Vec<Entry>
}
#[derive(Clone)]  
pub struct Entry {
    hashtag: String,
    popularity: i32,
}

impl TrendTracker {
    pub fn new() -> Self {
        Self { e: Vec::new() }
    }
    pub fn insert(&mut self ,ht: String){
        for i in self.e.iter(){
            if i.hashtag == ht {
                return;
            }
        }
        self.e.push(Entry{hashtag: ht, popularity: 0});
    }
    pub fn size(&mut self) -> i32 {
        self.e.len() as i32
    }
    pub fn tweeted(&mut self, ht: String){
        for  i in self.e.iter_mut(){
            if i.hashtag == ht {
                i.popularity += 1;
            }
        }
    }
    pub fn popularity(&mut self, hashtag: String) -> i32 {
        self.e
            .iter()
            .find(|entry| entry.hashtag == hashtag)
            .map(|entry| entry.popularity)
            .unwrap_or(-1)
    }
    pub fn top_trend(&mut self)-> String {
        if self.e.len() == 0 {
            return "".to_string();
        }
        else
        {
            let most_popular = self.e.iter_mut().max_by_key(|entry| entry.popularity).unwrap();
            return most_popular.hashtag.clone();
        }
    }
    // Fills the provided vector with the 3 most-tweeted hashtags,
    // in order from most-tweeted to least-tweeted.
    //
    // If there are fewer than 3 hashtags, then the vector is filled
    // with all hashtags (in most-tweeted to least-tweeted order).
    //
    // Must run in O(n) time.  
    pub fn top_three_trends(&mut self, trend: &mut Vec<String>) -> Vec<String> {
        if self.e.is_empty() {
            return vec![];
        }
        else
        {
            // sort by popularity
            // return top 3 hashtags
            let mut sorted = self.e.clone();
            sorted.sort_by(|a, b| b.popularity.cmp(&a.popularity));
            for i in sorted.iter().take(3) {
                trend.push(i.hashtag.clone());
            }
            return trend.clone();
        }
    }
    pub fn remove(&mut self, ht: String){
        self.e.retain(|entry| entry.hashtag != ht);
    }
    // Fills the provided vector with the k most-tweeted hashtags,
    // in order from most-tweeted to least-tweeted.
    //
    // If there are fewer than k hashtags, then the vector is filled
    // with all hashtags (in most-tweeted to least-tweeted order).
    //
    // Must run in O(nk) time.
    pub fn top_k_trends(&mut self, k: i32,  trend: &mut Vec<String>){
        trend.is_empty();
    }
}