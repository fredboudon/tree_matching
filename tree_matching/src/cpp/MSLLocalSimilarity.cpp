#include "MSLSimilarity.h"
#include <iostream>
#include <strstream>
#include <cstdio>
#include <cmath>

//--------------------------------------------------------------------------------
// Calcul du co�t local d'insertion d'un noeud
//------------------------------------------------------------------------
float MSLSimilarity::insLocalNode(TreeGraph* T, int w){
  float Dist;
  
  int wReal = T->getRealNumber(w);  
  TreeNode* _node =  T->getNode(wReal);
  
  //Si il ne s'agit pas de la derni�re �chelle de comparaison 
  if(T->getMTG()->vscale(_node->getVertex()) < _init){
    VId root = _node->getVertex();
    TreeGraph* Tree2 = new TreeGraph(*(T->getMTG()),root,COMPO);
    int nbVertex = Tree2->getNbVertex();
    
    //somme des co�ts d'insertion des sous-noeuds � l'�chelle courante+1 
    Dist = 0 ;
    for(int i =0; i<nbVertex;i++ ){    
      Dist = Dist + insLocalNode(Tree2,i);
    } 
    
    delete (TreeGraph*) Tree2;
    
  }
  else
    {
      //sinon co�t d'insertion suivant la fonction co�t utilis�
      
      //FSetArray fs =  T->getMTG()->featuresArray();
      //Feature * f = fs[_node->getVertex()];
      //Dist =CostMatrix->getInsertionCost(_node);
      
      //Dist =CostMatrix1[symbols["-"]][symbols[f[0].s]];
      Dist = -1;
    }
  
  
  return Dist;
}

//--------------------------------------------------------------------------------
// Calcul du co�t local de suppression d'un noeud
//------------------------------------------------------------------------
float MSLSimilarity::delLocalNode(TreeGraph* T, int v){
  float Dist;
  
  
  int vReal = T->getRealNumber(v);
  TreeNode* _node =  T->getNode(vReal);
  
  //Si il ne s'agit pas de la derni�re �chelle de comparaison 
  if(T->getMTG()->vscale(_node->getVertex()) < _init){
    VId root = _node->getVertex();
    TreeGraph* Tree1 = new TreeGraph(*(T->getMTG()),root,COMPO);
    int nbVertex = Tree1->getNbVertex();
    
    //somme des co�ts de suppression des sous-noeuds � l'�chelle courante+1 
    Dist = 0 ;
    for(int i =0; i<nbVertex;i++ ){
      Dist = Dist + delLocalNode(Tree1,i);
    } 
    
    delete (TreeGraph*) Tree1;
    
  } 
  else
    {
      //sinon co�t de suppression suivant la fonction co�t utilis�
      //Dist = CostMatrix->getDeletionCost(_node);    
      //FSetArray fs =  T->getMTG()->featuresArray();
      //Feature * f = fs[_node->getVertex()];
      
      //Dist =CostMatrix1[symbols[f[0].s]][symbols["-"]];
      Dist = -1;
    }
  
  return Dist;
}

//--------------------------------------------------------------------------------
// Calcul du co�t local de remplacement d'un noeud par un autre
//------------------------------------------------------------------------
float MSLSimilarity::matchLocalNode(int v, int w){
  float Dist;
  int vReal = T1->getRealNumber(v);
  int wReal = T2->getRealNumber(w);
  
  TreeNode* _node1 =  T1->getNode(vReal);
  TreeNode* _node2 =  T2->getNode(wReal);
  
  //Si il ne s'agit pas de la derni�re �chelle de comparaison 
  if(T1->getMTG()->vscale(_node1->getVertex()) < _init){
    VId root1 = _node1->getVertex();
    TreeGraph* Tree1 = new TreeGraph(*(T1->getMTG()),root1,COMPO);
    
    
    VId root2 = _node2->getVertex();
    TreeGraph* Tree2 = new TreeGraph(*(T2->getMTG()),root2,COMPO);
    
    
    //distance entre les sous-arborescences � l'�chelle courante+1 
    MSSimilarity* M=new MSSimilarity(*Tree1,*Tree2,*CostMatrix,_init);
    Dist=M->match();
    delete (MSSimilarity*) M;
    delete (TreeGraph*) Tree1;
    delete (TreeGraph*) Tree2;
  }
  else
    {
      //sinon co�t de remplacement suivant la fonction co�t utilis�
      //Dist = CostMatrix->getChangingCost(_node1,_node2);
      //FSetArray fs1 =  T1->getMTG()->featuresArray();
      //FSetArray fs2 =  T2->getMTG()->featuresArray();
      //Feature * f1 = fs1[_node1->getVertex()];
      //Feature * f2 = fs2[_node2->getVertex()];
      //Dist =CostMatrix1[symbols[f1[0].s]][symbols[f2[0].s]];
      Dist = 2;
    }
  
  return Dist;
}
