#!/usr/bin/env ruby

=begin

|-+. = Walls (all mean the same)
R = Ring (Treasure)
K = Key
E = Exit
H = Hero (Entrance, an SafeSpot)
L = Locked Gate (needs Key)
P = Pivot (center) of a door. 
D = Door Segment
N = Snake

=end

require 'pp'
require 'erb'

def parse_file(level_filename)
    level = { 
        map: [],
        spiders: [],
        keys: [],
        gates: [],
        rings: [],
        doors: [],
    }

    m = /level(\d+)\.txt$/.match(level_filename)
    if !m 
        raise "failed to match level filename #{level_filename}"
    end
    level[:number] = m[1].to_i

    content = File.read(level_filename)
    raise unless content;
    lines = content.split("\n")
    raise unless lines.count > 1
    file_width = lines.first.length
    puts "file width #{file_width}"
    file_height = lines.length
    puts "file height #{file_height}"

    (0..file_height-1).each do |y|
        level[:map][y] ||= [ 0 ] * file_width
        (0..file_width-1).each do |x|

            c = lines[y][x]
            case c
            when '|','-','+','.' then
                level[:map][y][x] = 1
            when 'H' then
                level[:hero] = [x,y]
            when 'E' then
                level[:exit] = [x,y]
            when 'S','N' then
                level[:spiders] << [x,y]
            when 'K' then
                level[:keys] << [x, y]
            when 'L' then
                level[:gates] << [x, y]
            when 'R' then
                level[:rings] << [x, y]
            when ' ' then
                # empty space
            when 'D' then
                # ignore door segment
            when 'P' then
                level[:doors] << process_door(lines,x, y)
            else
                raise "unknown map char '#{c}'"
            end
        end
    end

    # pp level

    return level
end

def process_door(lines, x, y)
    horizontal = lines[y][x+1] == 'D'
    return [x, y, horizontal]
end

def main
    Dir.glob("levels/level*.txt").each do |level_filename|
        level = parse_file(level_filename)
        write_level(level)
    end
end

def write_level(level)
    File.open("generated/level#{level[:number]}.cpp", 'w') do |file|
        template = ERB.new File.read('levelX.cpp.erb')
        file.puts template.result_with_hash(level)
    end
end


main