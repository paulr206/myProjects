//
//  ContentView.swift
//  MP3 TagEditor
//
//  Created by Paul Rübenich on 31.05.23.
//

import SwiftUI
import AVFoundation



struct ContentView: View {
    @State var mp3_files: [MP3File] = []
    @State var selected_file: MP3File
    
    @State private var selected = Set<MP3File.ID>()
    
    
    @State var inputFields: [String] = Array(repeating: "", count: 24)
        
    let columns = Array(repeating: GridItem(.flexible(minimum: 20)), count: 7)
    let rowTitles = ["A", "B", "C", "D"]
    
    
    var body: some View {
        VStack{
            //Menüleiste
            VStack{
                Button(action: {
                    Task {
                        do {
                            let panel = NSOpenPanel()
                            panel.allowsMultipleSelection = true
                            panel.canChooseDirectories = false
                            if panel.runModal() == .OK {
                                let tempData: MP3File? = MP3File()
                                await tempData?.open_MP3_file(url: panel.url)
                                if(tempData != nil) {
                                    self.mp3_files.append(tempData!)
                                }
                            }
                        }
                    }
                }) {
                    Image("folder")
                        .renderingMode(.original)
                        .frame(width: 100, height: 100)
                }
                
                Button(action: {
                    print(selected)
                    print(mp3_files[0].printID())
                }) {
                    Text("Test")
                }
            }
            // Daten
            HStack{
                // linke Seite zum Bearbeiten
                VStack {
                    Text("Filename: \(selected_file.get_file_name())")
                    Text("Name: \(selected_file.get_song_name())")
                    Text("Künstler: \(selected_file.get_artist())")
                    Text("Album: \(selected_file.get_album())")
                    Text("Jahr: \(selected_file.get_year())")
                    Text("Genre: \(selected_file.get_genre())")
                }
                // rechte Seite mit Liste der MP3's
                
                 Table(mp3_files, selection: $selected) {
                 TableColumn("Filename") { mp3_file in
                 Text(mp3_file.get_file_name())
                 }
                 TableColumn("Songname") { mp3_file in
                 Text(mp3_file.get_song_name())
                 }
                 TableColumn("Artist") { mp3_file in
                 Text(mp3_file.get_artist())
                 }
                 TableColumn("Album") { mp3_file in
                 Text(mp3_file.get_album())
                         .onTapGesture {
                             //print(selected)
                             
                             //set_selected_file()
                         }
                 }
                 TableColumn("Year") { mp3_file in
                 Text(mp3_file.get_year())
                 }
                 TableColumn("Genre") { mp3_file in
                 Text(mp3_file.get_genre())
                 }
                 }
                 .onTapGesture {
                     print(selected)
                     set_selected_file()
                 }
                 .scrollDisabled(false)
                 
/*
                 Table(of: MP3File.self, selection: $selected) {
                 TableColumn("Filename", value: \.file_name)
                 TableColumn("Songname", value: \.song_name)
                 TableColumn("Artist", value: \.artist)
                 TableColumn("Album", value: \.album)
                 TableColumn("Year", value: \.year)
                 TableColumn("Genre", value: \.genre)
                 } rows: {
                 ForEach(mp3_files) { file in
                 TableRow(file)
                 }
                 }

                Table(mp3_files, selection: $selected) {
                    TableColumn("Capital", value: \.capital) {
                        Text($0.capital ?? "")
                    }
                    TableColumn("Continent", value: \.continent)
                    TableColumn("Currency", value: \.currency) {
                        Text($0.currency ?? "")
                    }
                    TableColumn("Population", value: \.population) {
                        Text($0.formattedPopulation)
                    }
                    TableColumn("Area", value: \.area) {
                        Text($0.formattedArea)
                    }
                    TableColumn("Visited", value: \.visited) {
                        Text($0.visited ? "Yes" : "No")
                    }
                }
*/
                TableView()
                LazyVGrid(columns: columns) {
                            
                            // first headline row
                            Text("")
                            ForEach(1..<7) { i in
                                Text("\(i)").bold()
                            }
                            
                            // rows
                            ForEach(0..<4) { row in
                                Text(rowTitles[row]).font(.title)
                                ForEach(0..<6) { col in
                                    TextField("", text: $inputFields[row * 6 + col])
                                        .background(
                                            VStack {
                                                Spacer()
                                                Color.primary
                                                    .frame(width: 3, height: 1)
                                            }
                                        )
                                }
                            }
                        }
                        .padding()
            }
        }
    }
    
    func set_selected_file() -> Void {
        print(selected)
        let filteredObjects = mp3_files.filter { $0.id == selected.first }
        let foundObject = filteredObjects.first
        selected_file = foundObject!
    }
    
}



struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView(selected_file: MP3File.init())
    }
}




struct TableView: View {
    
    var body: some View {
        Text("Test")
    }
    
}
