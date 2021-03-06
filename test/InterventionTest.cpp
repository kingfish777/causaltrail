#include "gtest/gtest.h"
#include "../core/Interventions.h"
#include "config.h"
class InterventionTest : public ::testing::Test{
	protected:
	InterventionTest()
		:c(NetworkController())
	{
	}

	void virtual SetUp(){
		c.loadNetwork(TEST_DATA_PATH("Student.na"));
		c.loadNetwork(TEST_DATA_PATH("Student.sif"));
		c.loadObservations(TEST_DATA_PATH("StudentData.txt"),TEST_DATA_PATH("controlStudent.json"));
		c.trainNetwork();
	}

	public:
	NetworkController c;
	
};

TEST_F(InterventionTest, Constructor){
	Interventions i(c);
	SUCCEED();
}

TEST_F(InterventionTest, doInterventionEdges){
	Interventions i(c);
	Network& n = c.getNetwork();
	Node& grade = n.getNode("Grade");
	ASSERT_EQ(2u, grade.getParents().size());
	i.createBackupOfNetworkStructure();
	i.doIntervention("Grade","g3");
	ASSERT_EQ(0u, grade.getParents().size());
	i.reverseDoIntervention("Grade");
	i.loadBackupOfNetworkStructure();
	ASSERT_EQ(2u, grade.getParents().size());
}

TEST_F(InterventionTest, doInterventionProbabilities){
	Interventions i(c);
	Network & n = c.getNetwork();
	Node& grade = n.getNode("Grade");
	ASSERT_NEAR(0.3f,grade.getProbability(0,0),0.001);
	ASSERT_NEAR(0.05f,grade.getProbability(0,2),0.001);
	ASSERT_NEAR(0.9f,grade.getProbability(0,1),0.001);
	ASSERT_NEAR(0.5f,grade.getProbability(0,3),0.001);
	ASSERT_NEAR(0.4f,grade.getProbability(1,0),0.001);
	ASSERT_NEAR(0.25f,grade.getProbability(1,2),0.001);
	ASSERT_NEAR(0.08f,grade.getProbability(1,1),0.001);
	ASSERT_NEAR(0.3f,grade.getProbability(1,3),0.001);
	ASSERT_NEAR(0.3f,grade.getProbability(2,0),0.001);
	ASSERT_NEAR(0.7f,grade.getProbability(2,2),0.001);
	ASSERT_NEAR(0.02f,grade.getProbability(2,1),0.001);
	ASSERT_NEAR(0.2f,grade.getProbability(2,3),0.001);	
	i.createBackupOfNetworkStructure();
	i.doIntervention("Grade","g3");
	ASSERT_NEAR(0.0,grade.getProbability(0,0),0.001);
	ASSERT_NEAR(0.0f,grade.getProbability(0,2),0.001);
	ASSERT_NEAR(0.0f,grade.getProbability(0,1),0.001);
	ASSERT_NEAR(0.0f,grade.getProbability(0,3),0.001);
	ASSERT_NEAR(0.0f,grade.getProbability(1,0),0.001);
	ASSERT_NEAR(0.0f,grade.getProbability(1,2),0.001);
	ASSERT_NEAR(0.0f,grade.getProbability(1,1),0.001);
	ASSERT_NEAR(0.0f,grade.getProbability(1,3),0.001);
	ASSERT_NEAR(1.0f,grade.getProbability(2,0),0.001);
	ASSERT_NEAR(1.0f,grade.getProbability(2,2),0.001);
	ASSERT_NEAR(1.0f,grade.getProbability(2,1),0.001);
	ASSERT_NEAR(1.0f,grade.getProbability(2,3),0.001);	
	i.reverseDoIntervention("Grade");
	i.loadBackupOfNetworkStructure();
	ASSERT_NEAR(0.3f,grade.getProbability(0,0),0.001);
	ASSERT_NEAR(0.05f,grade.getProbability(0,2),0.001);
	ASSERT_NEAR(0.9f,grade.getProbability(0,1),0.001);
	ASSERT_NEAR(0.5f,grade.getProbability(0,3),0.001);
	ASSERT_NEAR(0.4f,grade.getProbability(1,0),0.001);
	ASSERT_NEAR(0.25f,grade.getProbability(1,2),0.001);
	ASSERT_NEAR(0.08f,grade.getProbability(1,1),0.001);
	ASSERT_NEAR(0.3f,grade.getProbability(1,3),0.001);
	ASSERT_NEAR(0.3f,grade.getProbability(2,0),0.001);
	ASSERT_NEAR(0.7f,grade.getProbability(2,2),0.001);
	ASSERT_NEAR(0.02f,grade.getProbability(2,1),0.001);
	ASSERT_NEAR(0.2f,grade.getProbability(2,3),0.001);		
}

TEST_F(InterventionTest, addEdgeNetworkStructure){
	Interventions i(c);
	Network& n = c.getNetwork();
	Node& letter = n.getNode("Letter");
	ASSERT_EQ(1u, letter.getParents().size());
	ASSERT_TRUE("Grade"==n.getNode(letter.getParents()[0]).getName());
	i.createBackupOfNetworkStructure();
	i.addEdge("SAT","Letter");
	ASSERT_EQ(2u, letter.getParents().size());
	ASSERT_TRUE("Grade"==n.getNode(letter.getParents()[0]).getName());
	ASSERT_TRUE("SAT"==n.getNode(letter.getParents()[1]).getName());
	i.loadBackupOfNetworkStructure();
	i.removeEdge("SAT","Letter");
	ASSERT_EQ(1u, letter.getParents().size());
	ASSERT_TRUE("Grade"==n.getNode(letter.getParents()[0]).getName());	
}

TEST_F(InterventionTest, addEdgeProbability){
	Interventions i(c);
	Network& n = c.getNetwork();
	Node& letter = n.getNode("Letter");
	Matrix<float> prob = letter.getProbabilityMatrix();
	ASSERT_EQ(2u, prob.getColCount());
	ASSERT_EQ(3u, prob.getRowCount());
	i.createBackupOfNetworkStructure();
	i.addEdge(3,4);
	c.trainNetwork();
	Matrix<float> probAdd = letter.getProbabilityMatrix();
	ASSERT_EQ(2u, probAdd.getColCount());
	ASSERT_EQ(6u, probAdd.getRowCount());
	i.loadBackupOfNetworkStructure();
	i.removeEdge(3,4);
	c.trainNetwork();
	Matrix<float> probNew = letter.getProbabilityMatrix();
	ASSERT_EQ(2u, probNew.getColCount());
	ASSERT_EQ(3u, probNew.getRowCount());
	i.createBackupOfNetworkStructure();
}

TEST_F(InterventionTest, removeEdgeNetworkStructure){
	Interventions i(c);
	Network& n = c.getNetwork();
	Node& letter = n.getNode("Letter");
	ASSERT_EQ(1u, letter.getParents().size());
	ASSERT_TRUE("Grade"==n.getNode(letter.getParents()[0]).getName());
	i.createBackupOfNetworkStructure();
	i.removeEdge("Grade","Letter");
	ASSERT_EQ(0u, letter.getParents().size());
	i.loadBackupOfNetworkStructure();
	i.addEdge("Grade","Letter");
	ASSERT_EQ(1u, letter.getParents().size());
	ASSERT_TRUE("Grade"==n.getNode(letter.getParents()[0]).getName());	

}

TEST_F(InterventionTest, removeEdgeProbability){
	Interventions i(c);
	Network& n = c.getNetwork();
	Node& letter = n.getNode("Letter");
	Matrix<float> prob = letter.getProbabilityMatrix();
	ASSERT_EQ(2u, prob.getColCount());
	ASSERT_EQ(3u, prob.getRowCount());
	i.createBackupOfNetworkStructure();
	i.removeEdge("Grade","Letter");
	c.trainNetwork();
	Matrix<float> probAdd = letter.getProbabilityMatrix();
	ASSERT_EQ(2u, probAdd.getColCount());
	ASSERT_EQ(1u, probAdd.getRowCount());
	i.loadBackupOfNetworkStructure();
	i.addEdge("Grade","Letter");
	c.trainNetwork();
	Matrix<float> probNew = letter.getProbabilityMatrix();
	ASSERT_EQ(2u, probNew.getColCount());
	ASSERT_EQ(3u, probNew.getRowCount());

}


