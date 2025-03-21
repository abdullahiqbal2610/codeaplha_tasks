//#include <iostream>
//#include <string>
//#include <iomanip>
//#include <vector>
//#include <limits>
//#include <cmath>
//
//using namespace std;
//
//const int terminal_width = 80;
//
//// function to center align a string based on a given width (default 80)
//string center(const string& s, int width = terminal_width) {
//    int pad = (width - s.size()) / 2;
//    return (pad > 0 ? string(pad, '   ') : "") + s;
//}
//
//// helper to clear the input buffer after invalid input
//void clearinputbuffer() {
//    cin.clear();
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//}
//
//// valid grade points (only these values are allowed)
//const double valid_grade_points[] = {
//    0.00, 1.00, 1.33, 1.67, 2.00, 2.33, 2.67, 3.00, 3.33, 3.67, 4.00
//};
//const int valid_grade_points_count = 11;
//
//// checks if the entered grade point is valid
//bool isvalidgradepoint(double gp) {
//    for (int i = 0; i < valid_grade_points_count; i++) {
//        if (fabs(valid_grade_points[i] - gp) < 1e-9)
//            return true;
//    }
//    return false;
//}
//
//// returns the letter grade for an individual subject based on its grade point
//string getlettergradeforsubject(double gradepoint) {
//    if (fabs(gradepoint - 0.00) < 1e-9) return "F";
//    if (fabs(gradepoint - 1.00) < 1e-9) return "D";
//    if (fabs(gradepoint - 1.33) < 1e-9) return "D+";
//    if (fabs(gradepoint - 1.67) < 1e-9) return "C-";
//    if (fabs(gradepoint - 2.00) < 1e-9) return "C";
//    if (fabs(gradepoint - 2.33) < 1e-9) return "C+";
//    if (fabs(gradepoint - 2.67) < 1e-9) return "B-";
//    if (fabs(gradepoint - 3.00) < 1e-9) return "B";
//    if (fabs(gradepoint - 3.33) < 1e-9) return "B+";
//    if (fabs(gradepoint - 3.67) < 1e-9) return "A-";
//    if (fabs(gradepoint - 4.00) < 1e-9) return "A";
//    return "n/a";
//}
//
//// returns the overall letter grade based on the calculated cgpa using ranges
//string getlettergradeforcgpa(double cgpa) {
//    if (cgpa < 0.50)               return "F";
//    else if (cgpa < 1.16)          return "D";
//    else if (cgpa < 1.50)          return "D+";
//    else if (cgpa < 1.84)          return "C-";
//    else if (cgpa < 2.16)          return "C";
//    else if (cgpa < 2.50)          return "C+";
//    else if (cgpa < 2.84)          return "B-";
//    else if (cgpa < 3.16)          return "B";
//    else if (cgpa < 3.50)          return "B+";
//    else if (cgpa < 3.84)          return "A-";
//    else                          return "A";
//}
//
//int main() {
//    // ---------- initial header ----------
//    cout << "\033[1;32m" << center("CGPA calculator") << "\033[0m\n";
//    cout << "\033[1;33m" << center("by Muhammad Abdullah Iqbal") << "\033[0m\n\n";
//
//    // ---------- grade mapping table ----------
//    cout << "\033[1;35m" << center("grade to grade point mapping") << "\033[0m\n\n";
//
//    // use a margin to push the table further to the right (12 spaces)
//    string grademargin = "            ";
//
//    // table header
//    cout << grademargin << "\033[1;34m"
//        << left << setw(15) << "grade point"
//        << setw(15) << "letter grade"
//        << "\033[0m\n";
//
//    cout << grademargin << "\033[1;34m"
//        << string(15, '-')
//        << " " << string(15, '-')
//        << "\033[0m\n";
//
//    // table rows (loop through the allowed grade points)
//    for (int i = 0; i < valid_grade_points_count; i++) {
//        double gp = valid_grade_points[i];
//        string letter = getlettergradeforsubject(gp);
//        cout << grademargin << left << setw(15) << fixed << setprecision(2) << gp
//            << setw(15) << letter << "\n";
//    }
//
//    cout << "\n";
//
//    // ---------- input section ----------
//    int numsubjects = 0;
//    while (true) {
//        cout << "\033[1;36m" << center("enter the number of subjects:") << "\033[0m";
//        cin >> numsubjects;
//        if (!cin.fail() && numsubjects > 0) {
//            clearinputbuffer();
//            break;
//        }
//        else {
//            cout << "\033[1;31m" << center("invalid number of subjects. please try again.") << "\033[0m\n";
//            clearinputbuffer();
//        }
//    }
//
//    vector<string> coursenames(numsubjects);
//    vector<int> credithours(numsubjects);
//    vector<double> gradepoints(numsubjects);
//
//    // for each subject, get course name, credit hours, and valid grade point
//    for (int i = 0; i < numsubjects; i++) {
//        cout << "\n\033[1;36m" << center("enter details for course " + to_string(i + 1)) << "\033[0m\n";
//
//        // course name
//        cout << "\033[1;36m" << center("course name:") << "\033[0m ";
//        getline(cin, coursenames[i]);
//
//        // credit hours
//        while (true) {
//            cout << "\033[1;36m" << center("credit hours for " + coursenames[i] + ":") << "\033[0m ";
//            cin >> credithours[i];
//            if (!cin.fail() && credithours[i] > 0) {
//                clearinputbuffer();
//                break;
//            }
//            else {
//                cout << "\033[1;31m" << center("invalid credit hours. please enter a positive integer.") << "\033[0m\n";
//                clearinputbuffer();
//            }
//        }
//
//        // grade points
//        while (true) {
//            cout << "\033[1;36m"
//                << center("grade points for " + coursenames[i] + " (0.00, 1.00, 1.33, 1.67, 2.00, 2.33, 2.67, 3.00, 3.33, 3.67, 4.00):")
//                << "\033[0m ";
//            cin >> gradepoints[i];
//            if (!cin.fail() && isvalidgradepoint(gradepoints[i])) {
//                clearinputbuffer();
//                break;
//            }
//            else {
//                cout << "\033[1;31m" << center("invalid grade point! must be one of the listed values.") << "\033[0m\n";
//                clearinputbuffer();
//            }
//        }
//    }
//
//    //// ---------- cgpa calculation ----------
//    //double totalgradepoints = 0.0;
//    //int totalcredits = 0;
//    //for (int i = 0; i < numsubjects; i++) {
//    //    totalgradepoints += (gradepoints[i] * credithours[i]);
//    //    totalcredits += credithours[i];
//    //}
//    //double cgpa = (totalcredits > 0) ? totalgradepoints / totalcredits : 0.0;
//    //string finallettergrade = getlettergradeforcgpa(cgpa);
//
//    //// ---------- displaying the report card ----------
//    //cout << "\n\033[1;35m" << center("*************** student result card ***************") << "\033[0m\n\n";
//
//    //// adjusted margin to push the table further right (12 spaces)
//    //string margin = "            ";
//
//    //// table header
//    //cout << margin << "\033[1;34m"
//    //    << left << setw(25) << "course name"
//    //    << setw(15) << "credit hours"
//    //    << setw(15) << "grade points"
//    //    << setw(15) << "letter grade"
//    //    << "\033[0m\n";
//
//    //cout << margin << "\033[1;34m"
//    //    << string(25, '-')
//    //    << " " << string(14, '-')
//    //    << " " << string(14, '-')
//    //    << " " << string(14, '-')
//    //    << "\033[0m\n";
//
//    //// table rows
//    //for (int i = 0; i < numsubjects; i++) {
//    //    string letter = getlettergradeforsubject(gradepoints[i]);
//    //    cout << margin << left << setw(25) << coursenames[i]
//    //        << setw(15) << credithours[i]
//    //        << setw(15) << fixed << setprecision(2) << gradepoints[i]
//    //        << setw(15) << letter << "\n";
//    //}
//
//    //// final summary results
//    //cout << "\n" << margin << "\033[1;32mtotal credits: \033[0m" << totalcredits << "\n";
//    //cout << margin << "\033[1;32mcgpa: \033[0m" << fixed << setprecision(2) << cgpa << "\n";
//    //cout << margin << "\033[1;32mfinal letter grade: \033[0m" << finallettergrade << "\n\n";
//
//    //cout << "\033[1;35m" << center("*****************************************************") << "\033[0m\n";
//
//    return 0;
//}
