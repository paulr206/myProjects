//
//  MP3_TagEditorApp.swift
//  MP3 TagEditor
//
//  Created by Paul Rübenich on 31.05.23.
//

import SwiftUI

@main
struct MP3_TagEditorApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView(selected_file: MP3File(file_url: nil, file_name: "LinkinPark-Numb-Meteora-2003.mp3", song_name: "Numb", artist: "Linkin Park", album: "Meteora", year: "2003", genre: "Rock"))
        }
    }
}
