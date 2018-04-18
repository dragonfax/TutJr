#!/usr/bin/env ruby

=begin

R = Ring (Treasure)

=end

require 'pp'
require 'erb'

WALL_CHARS = %w{ | - + . }

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
            if WALL_CHARS.include?(c) 
                level[:map][y][x] = 1
            elsif c == 'H'
                level[:hero] = [x,y]
            elsif c == 'E'
                level[:exit] = [x,y]
            elsif c == 'S'
                level[:spiders] << [x,y]
            elsif c == 'K'
                level[:keys] << [x, y]
            elsif c == 'L'
                level[:gates] << [x, y]
            elsif c == 'R'
                level[:rings] << [x, y]
            elsif c == ' '
                # empty space
            elsif c == 'D' 
                # ignore door segment
            elsif c == 'P'
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