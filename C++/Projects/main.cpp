#include <iostream>
#include <string>
#include <map>
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class BST
{
public:
  int max_sum;
  int max;
  int min;
  bool is_bst;
};
BST solve(TreeNode* root, int &ans)
{
  if(root == NULL)
  {
    return {0,INT_MAX,INT_MIN,false};
  }
  BST bst;

  BST lhs = solve(root->left,  ans);
  BST rhs = solve(root->right, ans);
  bst.max_sum = lhs.max_sum + rhs.max_sum + root->val;
  //update max and min for bst. check if root val is bigger and smaller than right and left
  bst.max = std::max(root->val, rhs.max);
  bst.min = std::min(root->val, lhs.min);

  //check for left and right if bst and check if root val is geater than left and less than right
  if(lhs.is_bst && rhs.is_bst &&(root->val>bst.min&& root->val<bst.max)){
    bst.is_bst = true;
  }
  else{
    bst.is_bst = false;
  }
  // check if bst is a BST and update ans for the max_sum
  if(bst.is_bst) ans = bst.max_sum;
  return bst;
}
int maxSumBST(TreeNode* root) {
  int max = 0;
  solve(root, max);
  return max;
}
int main()
{
  std::string x;
  std::cin>>x;
  TreeNode root = TreeNode(1);

  
  
  

  
  std::cout<<std::endl;
  return 0;
}