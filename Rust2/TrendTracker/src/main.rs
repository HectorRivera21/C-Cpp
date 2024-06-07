

fn main() {
}





mod trend_tracker;// use 
#[cfg(test)]
mod tests {
    use super::trend_tracker::TrendTracker;
    use super::*;

    #[test]
    pub fn test_insert() {
        let mut tracker = TrendTracker { e: Vec::new() };
        tracker.insert("test1".to_string());
        assert_eq!(tracker.e.len(), 1);
    }

    #[test]
    pub fn test_size() {
        let mut tracker = TrendTracker { e: Vec::new() };
        tracker.insert("test1".to_string());
        assert_eq!(tracker.size(), 1);
    }

    #[test]
    pub fn test_tweeted() {
        let mut tracker = TrendTracker { e: Vec::new() };
        tracker.insert("test1".to_string());
        tracker.tweeted("test1".to_string());
        assert_eq!(tracker.popularity("test1".to_string()), 1);
    }

    #[test]
    pub fn test_popularity() {
        let mut tracker = TrendTracker { e: Vec::new() };
        tracker.insert("test1".to_string());
        tracker.tweeted("test1".to_string());
        assert_eq!(tracker.popularity("test1".to_string()), 1);
    }
    #[test]
    pub fn test_remove() {
        let mut tracker = TrendTracker { e: Vec::new() };
        tracker.insert("test1".to_string());
        tracker.tweeted("test1".to_string());
        tracker.remove("test1".to_string());
        assert_eq!(tracker.size(), 0);
    }
    #[test]
    pub fn test_top_trend() {    
        let mut tracker = TrendTracker { e: Vec::new() };
        tracker.insert("test1".to_string());
        tracker.tweeted("test1".to_string());
        assert_eq!(tracker.top_trend(), "test1".to_string());
    }
    #[test]
    pub fn test_top_three() {
        let mut tracker = TrendTracker { e: Vec::new() };
        let mut trend: Vec<String> =  Vec::new();
        tracker.insert("test1".to_string());
        tracker.tweeted("test1".to_string());
        tracker.insert("test2".to_string());
        tracker.tweeted("test2".to_string());
        tracker.tweeted("test2".to_string());
        tracker.insert("test3".to_string());
        tracker.tweeted("test3".to_string());
        tracker.tweeted("test3".to_string());
        tracker.tweeted("test3".to_string());
        assert_eq!(tracker.top_three_trends(&mut trend), vec!["test3".to_string(),"test2".to_string(),"test1".to_string()]);
    }
    // Add tests for other functions here
}