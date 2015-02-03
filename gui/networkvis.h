#ifndef NETWORKVIS_H
#define NETWORKVIS_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QListView>
#include "../core/NetworkController.h"

/**
 * This class is based on the Elastic Nodes Example from the Qt documentation:
 * http://doc.qt.io/qt-5/qtwidgets-graphicsview-elasticnodes-example.html#graphwidget-class-definition
 * (Accessed 31.01.2015)
 */

class Edge;
class NodeGui;
class NetworkVis : public QGraphicsView
{

    Q_OBJECT

public:
    /**
     * @brief NetworkVis
     * Constructor of the networkVisualization class
     * @param parent Pointer to the parent QWidget
     * @param nc
     */
    NetworkVis(QWidget *parent, NetworkController& nc);

    /**
     * @brief forceDirectedLayout
     * Layout the network using force directed layout algorithms
     */
    void forceDirectedLayout();

    /**
     * @brief getNodeGuiVec
     * @return A reference to a vector of pointers to all NodeGui objects included in the current scence
     */
    const std::vector<NodeGui*>& getNodeGuiVec();

    /**
     * @brief getEdgeVec
     * @return A reference to a vector of pointers to all Edge objects included in the current scence
     */
    const std::vector<Edge*>& getEdgeVec();

    /**
     * @brief getNode
     * @param id Identifier of the desired node
     * @return A pointer to the node with the given id
     */
    NodeGui* getNode(unsigned int id);

    /**
     * @brief sizeHint
     * Reimplementation of the sizeHint() function from QGraphicsScene()
     * @return QSize object
     */
    QSize sizeHint() const;

    /**
     * @brief setWidth
     * Set width of the network visualization
     * @param width New width of the network visualization
     */
    void setWidth(unsigned int width);

    /**
     * @brief doIntervention
     * @param id Identifier of the node upon which a do intervention should be performed / reversed
     * @param flag Bool indicating whether a do intervention should be performed or reversed
     */
    void doIntervention(unsigned int id, bool flag);

    /**
     * @brief removeEdge
     * Removes the edge from node id1 to node id2
     * @param id1 Identifier of the source node
     * @param id2 Identifier of the target node
     */
    void removeEdge(unsigned int id1, unsigned int id2);

    /**
     * @brief addEdge
     * @param id1 Identifier of the source node
     * @param id2 Identifier of the target node
     */
    void addEdge(unsigned int id1, unsigned int id2);

    /**
     * @brief removeNodeHighlighting
     * Removes the highlighting from all nodes in the network
     */
    void removeNodeHighlighting();

    /**
     * @brief removeEdgeHighlighting
     * Removes the highlighting from all edges in the network
     */
    void removeEdgeHighlighting();

    /**
     * @brief removeAdditionalEdges
     * Remove all additional edges
     */
    void removeAdditionalEdges();

    /**
     * @brief restoreEdges
     * Restore all edges to the original state
     */
    void restoreEdges();

    /**
     * @brief unDoDoInt
     * Remove all do interventions in the network
     */
    void unDoDoInt();

    /**
     * @brief restoreEdge
     * Restores the (previously deleted) edge from source to target
     * @param source Name of the source node
     * @param target Name of the target node
     */
    void restoreEdge(QString source, QString target);

    /**
     * @brief removeAdditionalEdge
     * Removes the previously added edge from source to target
     * @param source Name of the source node
     * @param target Name of the target node
     */
    void removeAdditionalEdge(QString source, QString target);

    /**
     * @brief getAddedEdgeIDs
     * @return A vector of pairs of identfiers for all added edges
     */
    std::vector<std::pair<unsigned int, unsigned int>> getAddedEdgeIDs();

    /**
     * @brief getRemovedEdgeIDs
     * @return A vector of pairs of identfiers for all removed edges
     */
    std::vector<std::pair<unsigned int, unsigned int>> getRemovedEdgeIDs();

    /**
     * @brief originalNodeState
     * Restores the original state for all nodes in the network
     */
    void originalNodeState();


protected:
    /**
     * @brief mousePressEvent
     * Handles the mouse press event. Removes the highlighting from all nodes and edges
     * @param event QMouseEvent pointer
     */
    void mousePressEvent(QMouseEvent* event);

private:
    /**
     * @brief scence_
     * Pointer to a QGraphicsScence object
     */
    QGraphicsScene *scence_;

    /**
     * @brief pointerVec_
     * Vector holding pointers to all NodeGui objects
     */
    std::vector<NodeGui*> pointerVec_;

    /**
     * @brief pointerVecEdges_
     * Vector holding pointers to all Edge objects
     */
    std::vector<Edge*> pointerVecEdges_;

    /**
     * @brief additionalEdges_
     * Vector holding pointers to all additional Edge objects
     */
    std::vector<Edge*> additionalEdges_;

    /**
     * @brief removedEdges_
     * Vector holding pointers to all removed Edge objects
     */
    std::vector<Edge*> removedEdges_;

    /**
     * @brief width_
     * Width of the network visualization
     */
    unsigned int width_;

    /**
     * @brief createLayout
     * Creates a grid layout for the current visualization
     * @param parent Pointer to the parent widget
     */
    void createLayout(QWidget *parent);

    /**
     * @brief createScene
     * Initialises the scence
     */
    void createScene();

    /**
     * @brief loadNoads
     * Generates NodeGui objects for all nodes contained in the given NetworkController object
     * @param nc Reference to a NetworkController object
     */
    void loadNoads(NetworkController& nc);

    /**
     * @brief loadEdges
     * Generates Edges objects for all edges contained in the given NetworkController object
     * @param nc Reference to a NetworkController object
     */
    void loadEdges(NetworkController& nc);

    /**
     * @brief keyPressEvent
     * Calls zoom in and zoom out depending on wheter the "+"-key or "-"-key is pressed
     * @param event Pointer to QKeyEvent
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief scaleView
     * Scales the current view depending on the given scaleFactor
     * @param scaleFactor ScaleFactor to scale the view
     */
    void scaleView(qreal scaleFactor);

    /**
     * @brief wheelEvent
     * Calls zoom in and zoom out depending on the wheel direction
     * @param event Pointer to QWheelEvent
     */
    void wheelEvent(QWheelEvent *event);

    /**
     * @brief zoomIn
     */
    void zoomIn();

    /**
     * @brief zoomOut
     */
    void zoomOut();

    /**
     * @brief shiftNodes
     * Shifts all nodes to the center of the visualization
     */
    void shiftNodes();

};

#endif // NETWORKVIS_H