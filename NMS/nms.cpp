#include<vector>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

class Box
{
  public:
    Box(int x1_, int y1_, int x2_, int y2_, float conf_): x1(x1_), y1(y1_), x2(x2_), y2(y2_), conf(conf_){}
    
    int x1;
    int y1;
    int x2;
    int y2;
    float conf;
};

static bool comp(Box box1, Box box2)
{
  return (box1.conf > box2.conf);
}

float IOU(Box box1, Box box2)
{
  float area1 = (box1.x2 - box1.x1) * (box1.y2 - box1.y1);
  float area2 = (box2.x2 - box2.x1) * (box2.y2 - box2.y1);
  float insect_w = min(box1.x2, box2.x2) - max(box1.x1, box2.x1); 
  float insect_h = min(box1.y2, box2.y2) - max(box1.y1, box2.y1);
  return insect_w * insect_h / (area1 + area2 - insect_w * insect_h);
}


vector<Box> NMS(vector<Box>& boxList, float threshod)
{
  sort(boxList.begin(), boxList.end(), comp);
  int length = boxList.size();
  bool* flag = new bool [length];
  memset(flag, 0, length);
  for(int i = 0; i < length; i++)
  {
    if(flag[i] == 1)
      continue;
    for(int j = i + 1; j < length; j++)
    {
      if(flag[j] == 1)
        continue;
      if(IOU(boxList[i], boxList[j]) > threshod)
        flag[j] = 1;
    }
  }
  vector<Box> res;
  for(int i = 0; i < length; i++)
  {
    if(flag[i] == 0)
      res.push_back(boxList[i]);
  }
  return res;
}

int main(int argc, char* argv[])
{
  Box box1(204, 102, 358, 250, 0.5);
  Box box2(257, 118, 380, 250, 0.7);
  Box box3(280, 135, 400, 250, 0.6);
  Box box4(255, 118, 360, 235, 0.7);
  vector<Box> boxList;
  boxList.push_back(box1);
  boxList.push_back(box2);
  boxList.push_back(box3);
  boxList.push_back(box4);
  
  vector<Box> res;
  float threshod = 0.3;
  res = NMS(boxList, threshod);
  
  for(Box box: res)
  {
    cout << box.x1 << " " << box.y1 << " " << box.x2 << " " <<
    box.y2 << endl;
  }
  
  return 0;
}



