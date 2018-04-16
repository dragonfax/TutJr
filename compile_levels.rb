#!/usr/bin/env ruby

=begin

R = Ring (Treasure)

=end

require 'pp'

WALL_CHARS = %w{ | - + . }

def write_level(level)
    File.open("generated/level#{level[:number]}.cpp", 'w') do |file|
        file.puts <<-EOF
        #include "headers.h"

        static const byte PROGMEM data[] = { 
        EOF

        level[:map].each do |row|
            row.each(2) do |first,second|
                file.puts "B" + (first<<4 | second) + ",\n"
            end
        end

        file.puts "};\n"
    end
end

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
    file_width = lines.first.length - 1
    file_height = lines.length

    # actual rooms (not walls)
    map_width = (file_width - 1 ) / 2
    map_height = (file_height - 1 ) / 2

    (0..map_width-1).each do |x|
        (0..map_height-1).each do |y|

            if WALL_CHARS.include?(lines[y][x]) 
                level[:map][y] ||= [ '0' * file_width ]
                level[:map][y][x] = 1
            else
                c = lines[y][x]
                if c == 'H'
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
                    # pass
                elsif c == 'D' || c == 'P'
                    # door segment, handled elsewhere
                else
                    raise "unknown map char '#{c}'"
                end
            end
        end
    end

    pp level

    # process door locations
    (0..file_width-1).each do |x|
        (0..file_height-1).each do |y|
            c = lines[y][x]
            if c == 'P'
                level[:doors] << process_door(line,x,y)
            end
        end
    end


    return level
end

def process_door(lines, x, y)
    north = false
    south = false
    west = false
    east = false

    x1,y1 = move_coord(x,y, :north)
    if lines[y1][x1] == 'D'
        north = true
    end

    x1,y1 = move_coord(x,y, :south)
    if lines[y1][x1] == 'D'
        south = true
    end

    x1,y1 = move_coord(x,y, :west)
    if lines[y1][x1] == 'D'
        west = true
    end

    x1,y1 = move_coord(x,y, :east)
    if lines[y1][x1] == 'D'
        east = true
    end

    return [x,y,directions_to_bitmask(north,south,west,east)]
end

def directions_to_bitmask(north, south, west, east)
    north = north ? 1 : 0
    south = south ? 1 : 0
    west = west ? 1 : 0
    east = east ? 1 : 0

    return north << 3 | south << 2 | west << 1 | east
end


def map_to_file_coord(x, y)
    return x * 2 + 1, y * 2 + 1
end

def move_coord(x, y, direction)
    modify_x, modify_y = direction_modifier(direction)

    x += modify_x
    y += modify_y

    return x,y
end

def direction_modifier(direction)
    modifier = nil
    if direction == :north
        modifier = [0,-1]
    elsif direction == :south
        modifier = [0, 1]
    elsif direction == :west
        modifier = [-1, 0]
    elsif direction == :east
        modifier = [1, 0]
    else
        raise
    end

    return i,j
end

def is_open(lines, x, y, direction)
    i, j = map_file_coord(x, y)

    modify_x, modify_y = direction_modifier(direction)

    i, j = move_coord(i, j, direction)

    return is_wall_char(lines[j][i])
end

def is_wall_char(c)
    return %w"| - . +".include?(c)
end

def main
    Dir.glob("levels/level*.txt").each do |level_filename|
        level = parse_file(level_filename)
        write_level(level)
    end
end

main