#ifndef DISCRETISATIONSELECTION_H
#define DISCRETISATIONSELECTION_H

#include <QtWidgets/QDialog>

#include "../core/Matrix.h"
#include "../core/DiscretisationSettings.h"

#include "methodcombobox.h"

namespace Ui {
class DiscretisationSelection;
}

class QLabel;
class QLineEdit;
class QAbstractButton;

class DiscretisationSelection : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DiscretisationSelection
     * Constructor of class DiscretisationSelection
     * @param parent The parent Widget
     * @param path The standard path to save files in CausalTrail
     * @param samples The filename of the samples file
     * @param index The index of the current Session
     */
    DiscretisationSelection(QWidget* parent);

    /**
     * Show and reconfigure the dialog
     */
    void show(const QString& samples);

    /**
     * Get the sample file.
     */
    const QString& samples() const;

    /**
     * Get the chosen discretisation settings.
     */
    const DiscretisationSettings& getPropertyTree() const;

    /**
     * Get the chosen discretisation settings.
     */
    void generatePropertyTree();

    /**
     * Get the configured index.
     */
    int index() const;

    /**
     * @brief adaptGUIToData
     * Adapts the GUI to fit to the samples contained in the sample file provided in the constructor
     */
    void adaptGUIToData();

    /**
     * @brief ~DiscretisationSelection()
     * Destructor of this class
     */
    ~DiscretisationSelection();

    /**
     * Saves the selected discretisation methods in a user specified file
     */
    void saveDiscretisations();


	const QString& getControlFileName() const;

	void loadControlFile();


private slots:
	/**
	 * Slot which is called when a button in the
	 * QDialogButtonBox has been clicked.
	 */
	void clicked(QAbstractButton* btn);

    /**
     * @brief box_Index_Changed
     * @param position Index of the ComboBox that was changed
     * @param index New itemIndex of the ComboBox
     */
    void box_Index_Changed(uint position, const QString& method);

private:
    /**
     * @brief samples_
     * Name of the file containing samples_
     */
    QString samples_;

    /**
     * @brief controlFileName_
     * Name of the file containing discretisation information
     */
    QString controlFileName_;

    /**
     * @brief index_
     * Index of the corresponding NetworkInstance
     */
    int index_;

    /**
     * @brief ui
     * Graphical User Interface
     */
    Ui::DiscretisationSelection* ui;

    /**
     * @brief newMethodSelection
     * Creates a new MethodComboBox object representing all available discretisation methods
     * @param i Index of the methodComboBox
     * @return Pointer to a MethodComboBox Object
     */
    methodComboBox* newMethodSelection(unsigned int i);

    /**
     * @brief newOptionalValue
     * Creates a new QLineEdit object. It enables the user to enter optional values for the discretisation
     * @return Pointer to a QLineEdit Object
     */
    QLineEdit* newOptionalValue();

	QValidator* intValidator_;
	QValidator* doubleValidator_;


    /**
     * @brief featuresNames_
     * vector holding pointers to all QLineEdit Objects for the feature names
     */
    std::vector<QLabel*> featureNames_;

    /**
     * @brief boxes_
     * vector holding pointers to all MethodComboBox Objects
     */
    std::vector<methodComboBox*> boxes_;

    /**
     * @brief optionalValues_
     * vector holding pointers to all QLineEdit Objects for the optional values
     */
    std::vector<QLineEdit*> optionalValues_;

    /**
     * @brief propertyTree_
     * DiscretisationSettings object
     */
    DiscretisationSettings propertyTree_;

    /**
     * Get the parameter name corresponding to the selected methodIndex.
     */
    std::string getParameterName_(const std::string& method) const;

    /**
     * @brief sizeHint
     * @return A QSize object
     */
    QSize sizeHint() const;

	/**
	 * Sets the parameter field of the specified node.
	 */
	void setOptionalValue_ (size_t i, const DiscretisationSettings& propertyTree_, const std::string& nodeName );
};

#endif // DISCRETISATIONSELECTION_H
