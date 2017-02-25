/*
 * prog10_acd21.cpp
 *
 *  Created on: Dec 5, 2013
 *      Author: Adam C. De Leon
 *      Description: This program is intended for use by the Enigmatic Widget
 *      Company. The program uses information from an input file called
 *      EWCMaster.txt which contains on each of the file has an integer
 *      product ID, short name (with no spaces and a max length of 20
 *      characters), the cost of the product , a reorder level for the
 *      product, and a reorder amount for the product. The program also uses
 *      another input file (EWCinventory.txt) which contains only the product
 *      ID and an inventory count on each line. The program reads the data
 *      from the input file EWCMaster.txt into an array of structures and then
 *      updates the structure with the latest inventory. The program then
 *      produces a list of products that need to be reordered  which contains
 *      the product ID, product name, amount to reorder, cost, and total cost
 *      for the reorder of the item. This report is written to an output file
 *      (prog10_out_acd21.txt) The programs also validates that each input
 *      file was opened successfully and that the output file was created
 *      successfully with early returns.
 *
 *      Return 1: Error, Displays that input file EWCMaster.txt was not
 *      		  successfully opened.
 *
 *      Return 2: Error, Displays that input file EWCInventory.txt was not
 *      		  successfully opened and/ or that the reorder report in the
 *      		  output file prof10_out_acd21.txt was not successfully
 *      		  created.
 */
# include <iostream>
# include <fstream>
# include <iomanip>

using namespace std;

const int SIZE = 20;            // Max amount of characters for name.
const int MAX_NUM_PRODUCT = 15;    // Max amount of products.

struct product {    // Structure for relevant info in EWCMaster.txt
    int id_number;
    char name[SIZE + 1];
    double cost;
    int reorder_level;
    int reorder_amt;
};


bool GetMaster(product []);        // Prototypes for functions.
bool ReorderReport(product []);

int main() {
    product num_products[MAX_NUM_PRODUCT]; //name for array


    // Validate input file EWCMaster.txt was successfully opened.
    if (!GetMaster(num_products)) {
        cout << "Input file EWCMaster.txt could not be found." << endl;
        return 1;
    }

    /* Validate input file EWCInventory.txt was found and that reorder report
     * was successfully created. */
    if (!ReorderReport(num_products)) {
        cout << "Input file EWCinventory.txt could not be found and/ or "
                "reorder report was not successfully created." << endl;
        return 2;
    }

    return 0;
}

/*****************************************************************************
 * GetMaster - This function reads in the master inventory file.
 * The parameters of the function are the array of 'product’. The function
 * returns ‘true’ if the master file is successfully accessed and ‘false’
 * otherwise.
 */
bool GetMaster(product name[]) {
    bool success;                    // variable for bool return.
    ifstream fin_master;            // Input file object for EWCMaster.txt
    fin_master.open("EWCMaster.txt"); //Open the input file.

    if (fin_master) {
        // Load the structure with the information.
        for (int i = 0; i < MAX_NUM_PRODUCT; i++) {
            fin_master >> name[i].id_number;
            fin_master >> name[i].name;
            fin_master >> name[i].cost;
            fin_master >> name[i].reorder_level;
            fin_master >> name[i].reorder_amt;
        }

        // Close the input file EWCMaster.txt
        fin_master.close();

        success = true;
    } else
        success = false;

    return success;
}

/*****************************************************************************
 * ReorderReport -This function has as its parameter the array of product that
 * reads the inventory file and produces the reorder report. It will return
 * ‘true’ if the report is successfully generated and ‘false’ if it is not.
 * Note: It returns ‘true’ if both the inventory file opened successfully and
 * the report file was created successfully. If either fail the function
 * should displays an appropriate message to the console and return ‘false’.
 */
bool ReorderReport(product name[]) {
    bool success;            // variable for bool variable.
    int prod_id;            // other necessary variables for function.
    int inv_amount;
    double total_cost;

    ifstream fin_inventory; // Input file object for EWCInventory.txt
    ofstream fout;            // Output file object

    fin_inventory.open("EWCInventory.txt");// Open input file EWCInventory.txt
    fout.open("prog10_out_acd21.txt");       // Open the output file.

    // Header for output file.
    fout << "ID" << setw(6) << "Name" << setw(25) << "Reorder Amount"
         << setw(15) << "Cost" << setw(15) << "Total" << endl;

    if (fin_inventory) {
        // Read in product ID
        while (fin_inventory >> prod_id) {
            // Read in on hand inventory amounts
            fin_inventory >> inv_amount;

            // Process the reorder report.
            for (int i = 0; i < MAX_NUM_PRODUCT; i++) {
                // Match ID numbers
                if (name[i].id_number == prod_id) {
                    // Compare on hand amount to reorder level
                    if (name[i].reorder_level >= inv_amount) {
                        // perform calculations and display info
                        fout << setprecision(2) << fixed;
                        total_cost = (name[i].cost * name[i].reorder_amt);
                        fout << name[i].id_number << "\t" << name[i].name
                             << setw(12) << name[i].reorder_amt <<
                             setw(19) << "$" << name[i].cost << setw(9)
                             << "$" << total_cost << endl;
                    }
                }
            }
        }
        success = true;        // Assign appropriate value for return.
        fin_inventory.close(); // Close the input file.
    } else
        success = false;
    fout.close();                // Close the output file.
    return success;
}
