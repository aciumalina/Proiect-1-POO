

for (int i = 0; i < nrVec; i++)
    for (int j = i + 1; j < nrVec; j++) {
        if (vec[i] <vec[j])
            swap(vec[i], vec[j]);
}
for (int i = 0; i < nrVec; i++) {
if (vec[i].getPrenume() != "Anonim")                    //in cazul in care inainte de sortare sterg un obiect de tip doctor (ceea ce presupune setarea prenumelui la "Anonim"), verific sa nu il afisez
    cout << string(vec[i])<<", rating "<<vec[i].getRating() << endl;
}