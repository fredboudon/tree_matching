#include "MSMatching.h"
#include <iostream>
#include <cstdio>
#include <cmath>

//--------------------------------------------------------------------------------
// Calcul du co�t local d'insertion d'un noeud
//------------------------------------------------------------------------
int MSMatching::insLocalNode(TreeGraph* T, int w){
  int Dist;
  
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
      Dist = CostMatrix->getCost("-","2");
    }
  
  
  return Dist;
}

//--------------------------------------------------------------------------------
// Calcul du co�t local de suppression d'un noeud
//------------------------------------------------------------------------
int MSMatching::delLocalNode(TreeGraph* T, int v){
  int Dist;
  
  
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
      Dist = CostMatrix->getCost("1","-");
    }
  
  return Dist;
}

//--------------------------------------------------------------------------------
// Calcul du co�t local de remplacement d'un noeud par un autre
//------------------------------------------------------------------------
DistanceType MSMatching::matchLocalNode(int v, int w){
  DistanceType Dist;
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
    MSMatching* M=new MSMatching(*Tree1,*Tree2,*CostMatrix,_init);
    Dist=M->match();
    delete (MSMatching*) M;
    delete (TreeGraph*) Tree1;
    delete (TreeGraph*) Tree2;
  }
  else
    {
      //sinon co�t de remplacement suivant la fonction co�t utilis�
      Dist = CostMatrix->getCost("1","2");	
    }
  return Dist;
}
